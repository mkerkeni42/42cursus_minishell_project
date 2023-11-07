/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:51:03 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/26 21:13:46 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*get_token_type(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp != NULL)
	{
		if (!ft_strcmp(tmp->tok, ""))
			tmp->type = "EMPTY";
		else if (!ft_strcmp(tmp->tok, "|"))
			tmp->type = "PIPE";
		else if (!ft_strcmp(tmp->tok, ">"))
			tmp->type = "GREATER";
		else if (!ft_strcmp(tmp->tok, ">>"))
			tmp->type = "D_GREATER";
		else if (!ft_strcmp(tmp->tok, "<"))
			tmp->type = "LESSER";
		else if (!ft_strcmp(tmp->tok, "<<"))
			tmp->type = "D_LESSER";
		else
			tmp->type = "STRING";
		tmp = tmp->next;
	}
	return (toks);
}

char	*get_ex_code_token(t_vars *var)
{
	char	*token;

	var->len = 2;
	var->start = var->line;
	token = (char *)ft_malloc(sizeof(char) * var->len + 1);
	ft_strlcpy(token, var->start, var->len + 1);
	var->line += 2;
	return (token);
}

int	check_spaces(char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (!*line)
		return (1);
	return (0);
}

int	handle_quote_case(t_vars *var)
{
	char	*quote;

	quote = var->line;
	if (check_quote_in_str(var, var->start, var->end))
		return (1);
	var->line++;
	while (*(var->line) != *quote)
		var->line++;
	return (0);
}
