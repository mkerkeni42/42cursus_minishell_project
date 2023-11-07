/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:18:56 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 14:52:36 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exp_env(t_data *sh)
{
	sh->j = -1;
	sh->expenv = (char **)ft_malloc(sizeof(char *) * arr_size(sh->myenv));
	while (sh->myenv[++sh->j])
	{
		sh->expenv[sh->j] = (char *)ft_malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(sh->expenv[sh->j], sh->myenv[sh->j], \
			(ft_strlen(sh->myenv[sh->j]) + 1));
	}
	sh->expenv[sh->j] = NULL;
}

char	*check_var(char *var)
{
	int		i;
	char	*final;

	i = 0;
	while (var && var[i] && var[i] != '=')
		i++;
	final = (char *)ft_malloc(sizeof(char) * (i + 1));
	i = -1;
	while (var[++i] && var[i] != '=')
		final[i] = var[i];
	final[i] = '\0';
	return (final);
}

void	update_envs(t_data *sh, char **tmp)
{
	sh->j = -1;
	sh->i = -1;
	sh->expenv = (char **)ft_malloc(sizeof(char *) * arr_size(tmp));
	if (sh->bool == 1)
		sh->myenv = (char **)ft_malloc(sizeof(char *) * \
			(arr_size(tmp) - undeclared_var(tmp)));
	while (tmp[++sh->j])
	{
		if (sh->bool == 1 && ft_strchr(tmp[sh->j], '='))
		{
			sh->myenv[++sh->i] = (char *)ft_malloc(sizeof(char) \
				* (ft_strlen(tmp[sh->j]) + 1));
			ft_strlcpy(sh->myenv[sh->i], tmp[sh->j], \
				(ft_strlen(tmp[sh->j]) + 1));
		}
		sh->expenv[sh->j] = (char *)ft_malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->expenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	free(tmp);
	if (sh->bool == 1)
		sh->myenv[++sh->i] = NULL;
	sh->expenv[sh->j] = NULL;
}

static void	get_tmp(t_data *sh, char **tmp, char *var)
{
	char	*var1;
	char	*var2;

	var1 = check_var(var);
	var2 = check_var(sh->expenv[sh->j]);
	if (!ft_strcmp(var1, var2))
	{
		tmp[sh->j] = (char *)ft_malloc(sizeof(char) * \
			(ft_strlen(var) + 1));
		ft_strlcpy(tmp[sh->j], var, \
			ft_strlen(var) + 1);
		sh->bool = 1;
		free(var1);
		free(var2);
		return ;
	}
	tmp[sh->j] = (char *)ft_malloc(sizeof(char) \
		* (ft_strlen(sh->expenv[sh->j]) + 1));
	ft_strlcpy(tmp[sh->j], sh->expenv[sh->j], \
		(ft_strlen(sh->expenv[sh->j]) + 1));
	free(var1);
	free(var2);
}

void	export_var(t_data *sh, char *var, int bool)
{
	char	**tmp;

	if (bool == 1 && check_var_name(var))
	{
		get_error_message(var, 9);
		return ;
	}
	sh->j = -1;
	tmp = ft_calloc(sizeof(char *), arr_size(sh->expenv) + 2);
	sh->bool = 0;
	while (sh->expenv[++sh->j])
		get_tmp(sh, tmp, var);
	end_function(sh, tmp, var);
}
