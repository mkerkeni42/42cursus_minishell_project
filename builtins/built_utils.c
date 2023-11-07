/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:39:01 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 14:53:40 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(t_data *sh)
{
	int	j;

	j = 0;
	while (sh->export->env[j] || sh->export->exp[j])
	{
		if (sh->export->env[j])
			free(sh->export->env[j]);
		if (sh->export->exp[j])
			free(sh->export->exp[j]);
		j++;
	}
	free(sh->export->env);
	free(sh->export->exp);
}

void	built_pwd(void)
{
	char	buffer[BUFF_SIZE];

	if (getcwd(buffer, BUFF_SIZE))
		printf("%s\n", buffer);
	else
		perror("minishell");
}

void	built_cd(t_data *sh)
{
	if (arr_size(sh->cmds) > 3)
	{
		get_error_message("cd", 6);
		return ;
	}
	update_oldpwd(sh);
	if (chdir(sh->cmds[1]) == -1)
		get_error_message("cd", 3);
	update_pwd(sh);
}

void	built_env(t_data *sh)
{
	int	i;

	i = -1;
	while (sh->myenv && sh->myenv[++i])
		printf("%s\n", sh->myenv[i]);
}

void	my_env(t_data *sh)
{
	sh->j = -1;
	sh->myenv = (char **)ft_malloc(sizeof(char *) * arr_size(sh->env));
	while (sh->env[++sh->j])
	{
		sh->myenv[sh->j] = (char *)ft_malloc(sizeof(char) \
			* (ft_strlen(sh->env[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], sh->env[sh->j], \
			(ft_strlen(sh->env[sh->j]) + 1));
	}
	sh->myenv[sh->j] = NULL;
}
