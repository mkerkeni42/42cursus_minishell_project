/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:27:08 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/03 14:29:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_files(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp && tmp->next)
	{
		if (is_chevron(tmp->type, 1))
		{
			if (!ft_strcmp(tmp->type, "GREATER")
				|| !ft_strcmp(tmp->type, "D_GREATER")
				|| !ft_strcmp(tmp->type, "LESSER"))
			{
				if (ft_strcmp(tmp->next->type, "SKIP"))
					tmp->next->type = "FILE";
			}
		}
		tmp = tmp->next;
	}
}

void	get_limiter(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp(tmp->type, "D_LESSER"))
			tmp->next->type = "LIMITER";
		tmp = tmp->next;
	}
}
