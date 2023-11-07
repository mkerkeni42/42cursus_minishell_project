/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:35:31 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/03 17:19:26 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_dot_cmd(t_vars *var, int i)
{
	if (var->cmd[i].args[0] && !ft_strcmp(var->cmd[i].args[0], "./minishell"))
	{
		update_shlvl(var);
		return (0);
	}
	else if (var->cmd[i].args[0] && !ft_strcmp(var->cmd[i].args[0], ".."))
	{
		get_error_message(var->cmd[i].args[0], 4);
		return (1);
	}
	else if ((var->cmd[i].args[0] && !ft_strcmp(var->cmd[i].args[0], "."))
		&& !var->cmd[i].args[0][1])
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		set_exit_status(2);
		return (1);
	}
	else if (var->cmd[i].args[0] && !ft_strncmp(var->cmd[i].args[0], "./", 2))
	{
		if (check_permission(var->cmd[i].args[0], 1))
			return (1);
	}
	return (0);
}

static char	*get_cmd_path(char *cmd, char *path)
{
	char	**splitted_paths;
	char	*cmd_path;
	char	*test_cmd_path;
	int		i;

	i = -1;
	if (!cmd || !path)
		return (NULL);
	splitted_paths = ft_split(path, ':');
	while (splitted_paths[++i])
	{
		test_cmd_path = ft_strjoin(splitted_paths[i], "/", 1);
		cmd_path = ft_strjoin(test_cmd_path, cmd, 1);
		if (access(cmd_path, X_OK) == 0)
		{
			free_tab(splitted_paths, i + 1);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(splitted_paths);
	return (NULL);
}

static char	*get_path(t_vars *var)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (var->sh->myenv[++i])
	{
		if (!ft_strncmp(var->sh->myenv[i], "PATH=", 5))
		{
			path = var->sh->myenv[i] + 5;
			break ;
		}
	}
	return (path);
}

int	exec_cmd(t_vars *var, int i)
{
	char	**cmds;

	cmds = var->cmd[i].args;
	var->path = get_path(var);
	if (cmds[0] && cmds[0][0] == '.')
		if (handle_dot_cmd(var, i))
			return (1);
	if (execve(cmds[0], cmds, var->sh->expenv) == -1)
	{
		if (var->cmd[i].args[0][0] == '/' && check_if_dir(var->cmd[i].args[0]))
			return (1);
		if (!get_cmd_path(cmds[0], var->path))
		{
			set_correct_status(var, cmds, i);
			return (1);
		}
		cmds[0] = get_cmd_path(cmds[0], var->path);
		if (execve(cmds[0], cmds, var->sh->expenv) == -1)
		{
			set_exit_status(errno);
			perror("minishell");
			return (1);
		}
	}
	return (0);
}
