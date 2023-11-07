/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:33:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/01 14:24:23 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_here_doc_input(t_vars *var, int i)
{
	t_input	*tmp;

	if (pipe(var->here_doc) == -1)
		perror("minishell");
	tmp = var->data[i];
	while (tmp)
	{
		ft_putstr_fd(tmp->input, var->here_doc[1]);
		tmp = tmp->next;
	}
	if (close(var->here_doc[1]) == -1)
		perror("minishell");
}

static void	access_child_process(t_vars *var, int *pfd, int i)
{
	set_termios(1);
	signal(SIGINT, command_signal);
	signal(SIGQUIT, command_signal);
	var->empty_pipe = 0;
	set_stdin_pipeline(var, pfd, var->tmp_fd, i);
	set_stdout_pipeline(var, pfd, i);
	var->sh->exit_pipe = 0;
	if (var->cmd[i].fdin == -1 || var->cmd[i].fdout == -1)
		exit(*get_exit_status());
	else if (is_builtin(var->cmd[i].args[0]))
	{
		var->sh->cmds = var->cmd[i].args;
		if (!ft_strcmp(var->cmd[i].args[0], "exit"))
			var->sh->exit_pipe = 1;
		exec_builtin(var->sh);
		exit(*get_exit_status());
	}
	else if (exec_cmd(var, i))
		exit(*get_exit_status());
	else
	{
		set_exit_status(0);
		exit(*get_exit_status());
	}
}

static void	handle_pipes(t_vars *var, int i)
{
	int	pfd[2];

	var->pids = (int *)ft_malloc(sizeof(int) * (var->pipe_nb + 1));
	while (++i < var->pipe_nb + 1)
	{
		if (var->cmd[i].fdin == -2)
			get_here_doc_input(var, i);
		if (pipe(pfd) == -1)
			get_fct_error();
		update_underscore(var, i);
		var->pids[i] = fork();
		if (var->pids[i] == -1)
			perror("minishell");
		else if (var->pids[i])
			var->cmd[i].pid = var->pids[i];
		if (var->pids[i] == 0)
			access_child_process(var, pfd, i);
		else
			ignore_signals();
		close_pipes(var, pfd, i);
		close_files(var, i);
		var->tmp_fd = dup(pfd[0]);
	}
}

int	create_processes(t_vars *var, t_data *sh)
{
	int	i;

	i = -1;
	var->pids = NULL;
	var->only_empty = 0;
	if (!check_only_empty_pipes(var))
		var->only_empty = 1;
	if (!var->pipe_nb && is_builtin(var->cmd[0].args[0])
		&& var->cmd[0].fdin != -1 && var->cmd[0].fdout != -1)
	{
		sh->exit_pipe = 0;
		handle_builtin(var, sh);
	}
	else if (!var->pipe_nb && var->cmd[0].args[0]
		&& !ft_strcmp(var->cmd[0].args[0], ""))
		get_error_message("", 4);
	else if (!var->pipe_nb && !ft_strcmp(var->toks->type, "SKIP"))
		return (0);
	else
	{
		handle_pipes(var, i);
		wait_for_processes(var);
		free(var->pids);
	}
	return (0);
}
