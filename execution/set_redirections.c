/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:49:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/31 18:13:40 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_std_stream(int fd, int std_stream)
{
	if (dup2(fd, std_stream) == -1)
	{
		perror("minishell");
		set_exit_status(1);
		exit(*get_exit_status());
	}
	if (close(fd) == -1)
	{
		perror("minishell");
		set_exit_status(1);
		exit(*get_exit_status());
	}
}

static void	get_pipe_data(t_vars *var, int tmp_fd, int i)
{
	if (!ft_strcmp(var->cmd[i].args[0], "cat") && !var->cmd[i].args[1]
		&& i < var->pipe_nb && is_empty_pipe(tmp_fd))
	{
		read_stdin();
		var->empty_pipe = 1;
	}
	else
		get_std_stream(tmp_fd, STDIN_FILENO);
}

void	set_stdin_pipeline(t_vars *var, int *pfd, int tmp_fd, int i)
{
	if (var->cmd[i].fdin == -2)
	{
		if (close(pfd[0]) == -1)
			perror("minishell");
		get_std_stream(var->here_doc[0], STDIN_FILENO);
	}
	else if (var->cmd[i].fdin != 0 && var->cmd[i].fdin != -1)
	{
		if (close(pfd[0]) == -1)
			perror("minishell");
		get_std_stream(var->cmd[i].fdin, STDIN_FILENO);
	}
	else if (i && var->cmd[i].fdin == 0 && !var->only_empty)
		get_pipe_data(var, tmp_fd, i);
	else
	{
		if (!ft_strcmp(var->cmd[i].args[0], "cat") && !var->cmd[i].args[1]
			&& var->cmd[i].fdin != -1 && !var->only_empty)
		{
			read_stdin();
			var->empty_pipe = 1;
		}
		if (close(pfd[0]) == -1)
			perror("minishell");
	}
}

void	set_stdout_pipeline(t_vars *var, int *pfd, int i)
{
	if (i < var->pipe_nb && var->cmd[i].fdout == 1)
	{
		if (var->empty_pipe == 1 && !var->only_empty)
		{
			set_null_stdout();
			if (close(pfd[1]) == -1)
				perror("minishell:");
		}
		else
			get_std_stream(pfd[1], STDOUT_FILENO);
	}
	else if (var->cmd[i].fdout != 1 && var->cmd[i].fdout != -1)
	{
		if (close(pfd[1]) == -1)
			perror("minishell");
		get_std_stream(var->cmd[i].fdout, STDOUT_FILENO);
	}
	else
		if (close(pfd[1]) == -1)
			perror("minishell");
	var->empty_pipe = 0;
}

void	close_files(t_vars *var, int i)
{
	if (var->cmd[i].fdin != 0 && var->cmd[i].fdin != -2
		&& var->cmd[0].fdin != -1)
	{
		if (close(var->cmd[i].fdin) == -1)
			perror("minishell");
	}
	if (var->cmd[i].fdout != 1 && var->cmd[i].fdout != -1)
	{
		if (close(var->cmd[i].fdout) == -1)
			perror("minishell");
	}
}
