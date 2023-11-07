/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/03 16:53:10 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_special_tok(t_vars *var)
{
	char	special_tok[2];
	char	*token;

	token = get_double_chevrons_token(var);
	if (token)
		return (token);
	var->len = 1;
	special_tok[0] = *(var->line);
	special_tok[1] = '\0';
	if (is_forbidden_char(special_tok[0]))
	{
		get_error_message(special_tok, 0);
		var->bool = 1;
		return (NULL);
	}
	if (check_question_mark(var, var->line, special_tok))
		return (NULL);
	token = (char *)ft_malloc(sizeof(char) * (var->len + 1));
	ft_strlcpy(token, special_tok, var->len + 1);
	var->line++;
	return (token);
}

static char	*get_string_tok(t_vars *var)
{
	char		*token;

	token = NULL;
	var->start = var->line;
	var->x = 0;
	if (handle_empty_quotes(var, &token))
		return (token);
	while (*(var->line) && !ft_isspace(*(var->line))
		&& !is_special_char(*(var->line)))
	{
		if (*(var->line) == '\"' || *(var->line) == '\'')
		{
			if (handle_quote_case(var))
			{
				var->bool = 1;
				return (NULL);
			}
		}
		var->line++;
	}
	var->end = var->line - 1;
	var->len = var->end - var->start + 1;
	token = (char *)ft_malloc(sizeof(char) * (var->len + 1));
	ft_strlcpy(token, var->start, var->len + 1);
	return (token);
}

static char	*get_token(t_vars *var)
{
	char	*token;

	token = NULL;
	var->len = 0;
	var->end = NULL;
	while (ft_isspace(*(var->line)))
		var->line++;
	var->start = var->line;
	if (is_special_char(*(var->line)))
		token = get_special_tok(var);
	else if (*var->line == '$' && *(var->line + 1) == '?')
		token = get_ex_code_token(var);
	else
		token = get_string_tok(var);
	return (token);
}

static int	get_token_list(t_vars *var, char *line)
{
	while (*(var->line))
	{
		var->start = line;
		var->token = get_token(var);
		if (!var->token)
		{
			if (var->bool == 1)
				return (1);
			else
				return (0);
		}
		var->tok = ft_lst_new(var->token);
		ft_lst_add_back(&(var->toks), var->tok);
		while (*(var->line) && ft_isspace(*(var->line)))
			var->line++;
	}
	return (2);
}

int	tokenize_line(char *line, t_vars *var)
{
	int	ret;

	var->line = line;
	if (*(var->line) == '?')
	{
		get_error_message("?", 0);
		return (1);
	}
	if (check_spaces(var->line))
		return (1);
	ret = get_token_list(var, line);
	if (ret == 1)
		return (1);
	if (ret == 0)
		return (0);
	var->toks = get_token_type(var->toks);
	if (parse_tokens(var))
		return (1);
	get_limiter(var->toks);
	if (check_limiter(var))
		return (1);
	handle_quotes(var);
	get_files(var->toks);
	return (0);
}
