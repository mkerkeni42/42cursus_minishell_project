/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:22:28 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/30 17:26:40 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_quoted_token(t_vars *var, char q_type)
{
	char	*quoted_tok;
	char	*start;

	quoted_tok = NULL;
	var->var = NULL;
	var->value = NULL;
	var->start++;
	start = var->start;
	while (*(var->start) && *(var->start) != q_type)
		var->start++;
	var->end = var->start - 1;
	var->len = var->end - start + 1;
	var->start++;
	quoted_tok = (char *)ft_malloc(sizeof(char) * (var->len + 1));
	ft_strlcpy(quoted_tok, start, var->len + 1);
	if (q_type == '\"')
		quoted_tok = get_var(quoted_tok, var, 0, 0);
	return (quoted_tok);
}

static char	*get_non_quoted_tok(t_vars *var)
{
	char	*str_tok;
	char	*start;

	str_tok = NULL;
	var->var = NULL;
	var->value = NULL;
	if (*(var->start) && *(var->start) != '\'' && *(var->start) != '\"')
	{
		start = var->start;
		while (*(var->start) && *(var->start) != '\''
			&& *(var->start) != '\"')
			var->start++;
		var->end = var->start - 1;
		var->len = var->end - start + 1;
		str_tok = (char *)ft_malloc(sizeof(char) * (var->len + 1));
		ft_strlcpy(str_tok, start, var->len + 1);
		var->y = 1;
		str_tok = get_var(str_tok, var, 0, 1);
	}
	return (str_tok);
}

static char	*expand_token(char *token, t_vars *var)
{
	char	*tmp_tok;
	char	*quoted_tok;
	char	*str_tok;
	char	quote_type;

	str_tok = NULL;
	tmp_tok = get_non_quoted_tok(var);
	while (*(var->start))
	{
		quote_type = get_quote_type(var->start);
		if (!get_quote_type(var->start))
			return (NULL);
		quoted_tok = get_quoted_token(var, quote_type);
		if (tmp_tok)
			tmp_tok = ft_strjoin(tmp_tok, quoted_tok, 2);
		else
			tmp_tok = quoted_tok;
		str_tok = get_non_quoted_tok(var);
		if (str_tok)
			tmp_tok = ft_strjoin(tmp_tok, str_tok, 2);
	}
	free(token);
	token = ft_strdup(tmp_tok);
	free(tmp_tok);
	return (token);
}

t_tok	*handle_no_quote_tok(t_vars *var, t_tok *tmp)
{
	if (tmp->tok[0] == '$')
		tmp->tok = get_var(tmp->tok, var, 1, 1);
	else
	{
		var->y = 1;
		tmp->tok = get_var(tmp->tok, var, 0, 1);
	}
	if (!ft_strcmp(tmp->tok, ""))
		tmp->type = "SKIP";
	return (tmp);
}

int	handle_quotes(t_vars *var)
{
	t_tok	*tmp;

	tmp = var->toks;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "STRING"))
		{
			if (check_if_empty_tok(tmp, var) == 1)
				continue ;
			var->start = tmp->tok;
			if (ft_strchr(tmp->tok, '\"') || ft_strchr(tmp->tok, '\''))
				tmp->tok = expand_token(tmp->tok, var);
			else if (ft_strchr(tmp->tok, '$'))
				tmp = handle_no_quote_tok(var, tmp);
		}
		tmp = tmp->next;
	}
	return (0);
}
