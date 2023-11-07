/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:03:13 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/01 16:08:26 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_data *sh)
{
	if (!ft_strcmp(sh->cmds[0], "echo"))
		built_echo(sh);
	else
	{
		set_exit_status(0);
		if (!ft_strcmp(sh->cmds[0], "exit"))
			built_exit(sh);
		else if (!ft_strcmp(sh->cmds[0], "cd"))
			built_cd(sh);
		else if (!ft_strcmp(sh->cmds[0], "pwd"))
			built_pwd();
		else if (!ft_strcmp(sh->cmds[0], "export"))
			built_export(sh);
		else if (!ft_strcmp(sh->cmds[0], "unset"))
			built_unset(sh);
		else if (!ft_strcmp(sh->cmds[0], "env"))
		{
			update_underscore_env(sh);
			built_env(sh);
		}
	}
}

void	update_underscore_env(t_data *sh)
{
	char	*underscore;

	underscore = "_=usr/bin/env";
	export_var(sh, underscore, 0);
}

void	handle_builtin(t_vars *var, t_data *sh)
{
	update_underscore(var, 0);
	var->orig_stdin = dup(STDIN_FILENO);
	var->orig_stdout = dup(STDOUT_FILENO);
	sh->cmds = var->cmd[0].args;
	if (var->cmd[0].fdin != 0 && var->cmd[0].fdin != -2
		&& var->cmd[0].fdin != -1)
		get_std_stream(var->cmd[0].fdin, STDIN_FILENO);
	if (var->cmd[0].fdout != 1 && var->cmd[0].fdout != -1)
		get_std_stream(var->cmd[0].fdout, STDOUT_FILENO);
	exec_builtin(sh);
	if (var->cmd[0].fdin != 0 && var->cmd[0].fdin != -2)
		dup2(var->orig_stdin, STDIN_FILENO);
	if (var->cmd[0].fdout != 1)
		dup2(var->orig_stdout, STDOUT_FILENO);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	return (0);
}
