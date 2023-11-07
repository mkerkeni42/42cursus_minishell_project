/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:25:15 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 14:14:19 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	undeclared_var(char **tmp)
{
	int	res;
	int	i;

	res = 0;
	i = -1;
	while (tmp[++i])
		if (!ft_strchr(tmp[i], '='))
			res++;
	return (res);
}

static	int	check_free(t_data *sh, char *var)
{
	int	i;
	int	bool;

	i = -1;
	bool = 0;
	if (ft_strchr(var, '='))
		bool = 1;
	while (sh->expenv[++i])
		free(sh->expenv[i]);
	i = -1;
	if (bool == 1)
		while (sh->myenv[++i])
			free(sh->myenv[i]);
	if (bool == 1)
		free(sh->myenv);
	free(sh->expenv);
	return (bool);
}

void	end_function(t_data *sh, char **tmp, char *var)
{
	if (sh->bool == 0)
	{
		tmp[sh->j] = (char *)ft_malloc(sizeof(char) * (ft_strlen(var) + 1));
		ft_strlcpy(tmp[sh->j], var, ft_strlen(var) + 1);
	}
	tmp[++sh->j] = NULL;
	sh->bool = check_free(sh, var);
	update_envs(sh, tmp);
}
