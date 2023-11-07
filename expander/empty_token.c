/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:54:25 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/03 16:49:46 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_empty_quotes(t_vars *var, char **token)
{
	if ((*(var->line) == '\"' && *(var->line + 1) == '\"')
		|| (*(var->line) == '\'' && *(var->line + 1) == '\''))
	{
		if (!*(var->line + 2))
		{
			var->line += 2;
			*token = ft_strdup("");
			return (1);
		}
	}
	return (0);
}

int	check_if_empty_tok(t_tok *tmp, t_vars *var)
{
	if (tmp->tok && tmp->tok[0] == '\"' && tmp->tok[1] == '$')
	{
		var->start = tmp->tok + 2;
		var->end = var->start;
		while (ft_isalnum(*(var->end)) || *(var->end) == '_'
			|| *(var->end) == '?')
			var->end++;
		if (*(var->end) == '\"' && !*(var->end + 1))
		{
			tmp->tok = get_var(tmp->tok, var, 0, 0);
			if (!ft_strcmp(tmp->tok, "\"\""))
			{
				tmp->type = "EMPTY";
				tmp = tmp->next;
				return (1);
			}
		}
	}
	else if (!ft_strcmp(tmp->tok, "$"))
	{
		tmp->type = "EMPTY";
		return (1);
	}
	return (0);
}
