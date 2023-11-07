/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:24:25 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/30 10:58:01 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_input	*ft_lstnew_input(void *content)
{
	t_input	*lstnew;

	lstnew = (t_input *)ft_malloc(sizeof(t_input));
	if (!lstnew)
		return (0);
	lstnew->input = content;
	lstnew->next = NULL;
	return (lstnew);
}

t_input	*ft_lstlast_input(t_input *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_input(t_input **lst, t_input *new)
{
	t_input	*newlst;

	if (!*lst)
		*lst = new;
	else
	{
		newlst = ft_lstlast_input(*lst);
		newlst->next = new;
	}
}

void	print_list_input(t_input *input)
{
	t_input	*tmp;

	tmp = input;
	while (tmp != NULL)
	{
		printf("%s", tmp->input);
		tmp = tmp->next;
	}
}

void	free_list_input(t_input **lst, int nb, int x)
{
	t_input	**list;
	t_input	*tmp;
	int		i;

	i = -1;
	list = lst;
	while (++i < nb + 1)
	{
		while (lst && lst[i] != NULL)
		{
			tmp = lst[i];
			lst[i] = lst[i]->next;
			if (x == 0)
				free(tmp->input);
			free(tmp);
		}
	}
	free (list);
}
