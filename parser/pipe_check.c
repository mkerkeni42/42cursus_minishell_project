/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:49:56 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/15 12:04:59 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_before_pipe(t_vars *var)
{
	t_tok	*tmp;

	tmp = var->pipeline;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "PIPE"))
		{
			if (!tmp->prev)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	get_nb_of_pipes(t_tok *toks)
{
	t_tok	*tmp;
	int		pipe_nb;

	tmp = toks;
	pipe_nb = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "PIPE"))
			pipe_nb++;
		tmp = tmp->next;
	}
	return (pipe_nb);
}

int	check_double_pipe(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->type, "PIPE"))
		{
			if (!ft_strcmp(tmp->next->type, "PIPE"))
			{
				get_error_message("|", 1);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
