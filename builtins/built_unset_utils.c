/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:36:22 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 14:11:37 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_tmp_expenv(t_data *sh, char **tmp)
{
	char	*var1;
	char	*var2;

	var1 = check_var(sh->cmds[sh->i]);
	var2 = check_var(sh->expenv[sh->j]);
	if (!ft_strcmp(var1, var2))
	{
		free(sh->expenv[sh->j]);
		free(var1);
		free(var2);
		return ;
	}
	tmp[sh->c] = (char *)ft_malloc(sizeof(char) \
		* (ft_strlen(sh->expenv[sh->j]) + 1));
	ft_strlcpy(tmp[sh->c], sh->expenv[sh->j], \
		(ft_strlen(sh->expenv[sh->j]) + 1));
	free(sh->expenv[sh->j]);
	sh->c++;
	free(var1);
	free(var2);
}

void	get_tmp_myenv(t_data *sh, char **tmp)
{
	char	*var1;
	char	*var2;

	var1 = check_var(sh->cmds[sh->i]);
	var2 = check_var(sh->myenv[sh->j]);
	if (!ft_strcmp(var1, var2))
	{
		free(sh->myenv[sh->j]);
		free(var1);
		free(var2);
		return ;
	}
	tmp[sh->c] = (char *)ft_malloc(sizeof(char) \
		* (ft_strlen(sh->myenv[sh->j]) + 1));
	ft_strlcpy(tmp[sh->c], sh->myenv[sh->j], \
		(ft_strlen(sh->myenv[sh->j]) + 1));
	free(sh->myenv[sh->j]);
	sh->c++;
	free(var1);
	free(var2);
}
