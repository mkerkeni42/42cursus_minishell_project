/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 16:39:23 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/11/28 14:39:25 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*next_lst;

	if (!lst || !del || !f)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		next_lst = ft_lstnew(f(lst->content));
		if (!next_lst)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back(&new_lst, next_lst);
		lst = lst->next;
	}
	next_lst->next = NULL;
	return (new_lst);
}
