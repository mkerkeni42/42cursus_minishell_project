/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 12:47:31 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/11/27 16:08:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del) (void *))
{
	t_list	*current;

	if (lst && del)
	{
		while (lst && *lst)
		{
			current = (*lst)->next;
			del((*lst)->content);
			free(*lst);
			*lst = current;
		}
		*lst = NULL;
	}
}
