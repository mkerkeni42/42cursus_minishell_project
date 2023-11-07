/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:36:49 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 16:48:37 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cpy_env(t_data *sh)
{
	sh->j = -1;
	while (sh->expenv[++sh->j])
	{
		sh->export->env[sh->j] = (char *)ft_malloc(sizeof(char) \
			* (ft_strlen(sh->expenv[sh->j]) + 1));
		ft_strlcpy(sh->export->env[sh->j], sh->expenv[sh->j], \
			(ft_strlen(sh->expenv[sh->j]) + 1));
	}
	sh->export->env[sh->j] = NULL;
}

static void	search_min(t_export *export, int i)
{
	int	index;
	int	k;

	index = 0;
	export->j = -1;
	while (export->env[++export->j])
	{
		k = 0;
		while (export->env[export->j][k] && export->env[index][k] &&
			export->env[export->j][k] == export->env[index][k])
			k++;
		if (export->env[export->j][k] < export->env[index][k])
			index = export->j;
	}
	export->j = index;
	export->exp[i] = (char *)ft_malloc(sizeof(char) \
		* (ft_strlen(export->env[export->j]) + 3));
}

static void	cpy_export(t_export *export, int j)
{
	int	i;
	int	k;
	int	bool;

	i = -1;
	k = -1;
	bool = 1;
	while (export->env[export->j][++i])
	{
		if (export->env[export->j][i] == '=' && bool == 1)
		{
			bool--;
			export->exp[j][++k] = export->env[export->j][i];
			export->exp[j][++k] = '"';
		}
		else
			export->exp[j][++k] = export->env[export->j][i];
	}
	if (ft_strchr(export->env[export->j], '='))
		export->exp[j][++k] = '"';
	export->exp[j][++k] = '\0';
}

int	arr_size(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len + 1);
}

void	built_export(t_data *sh)
{
	int	i;

	i = -1;
	sh->v = 0;
	while (sh->cmds[++sh->v])
		export_var(sh, sh->cmds[sh->v], 1);
	if (sh->v > 1)
		return ;
	sh->export = (t_export *)ft_malloc(sizeof(t_export));
	sh->export->exp = (char **)ft_malloc(sizeof(char *) * arr_size(sh->expenv));
	sh->export->env = (char **)ft_malloc(sizeof(char *) * arr_size(sh->expenv));
	cpy_env(sh);
	while (sh->export->env[++i])
	{
		search_min(sh->export, i);
		cpy_export(sh->export, i);
		sh->export->exp[i] = ft_strjoin("declare -x ", sh->export->exp[i], 3);
		sh->export->env[sh->export->j][0] = 126;
		printf("%s \n", sh->export->exp[i]);
		free(sh->export->exp[i]);
	}
	free_tab(sh->export->env, 0);
	free(sh->export->exp);
	free(sh->export);
}
