/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/30 14:57:40 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **tab)
{
	int	y;

	y = -1;
	while (tab[++y])
		printf("%s\n", tab[y]);
	printf("\n");
}

void	free_tab(char	**tab, int i)
{
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	init_data(t_vars *var)
{
	int	i;

	i = -1;
	while (++i < var->pipe_nb + 1)
		var->data[i] = NULL;
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		get_fct_error();
	return (ptr);
}

int	check_var_name(char *var)
{
	int	i;

	i = -1;
	if (!ft_strcmp(var, "") || var[0] == '=')
		return (1);
	if (var && var[0] >= '0' && var[0] <= '9')
		return (1);
	while (var && var[++i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (1);
	}
	return (0);
}
