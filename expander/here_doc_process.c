/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:40:05 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/01 14:27:31 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	here_doc_loop(t_vars *var, char *line, char *limiter)
{
	while (line)
	{
		line = readline("> ");
		line = ft_strjoin(line, "\n", 1);
		if (!line || !ft_strcmp(line, limiter))
		{
			free(line);
			free(limiter);
			close(var->pfd[1]);
			exit(0);
		}
		ft_putstr_fd(line, var->pfd[1]);
		free(line);
	}
}

static void	handle_hd_process(t_vars *var, char *limiter)
{
	char	*line;

	close(var->pfd[0]);
	set_termios(1);
	signal(SIGINT, here_doc_signal);
	line = readline("> ");
	line = ft_strjoin(line, "\n", 1);
	if (!line || !ft_strcmp(line, limiter))
	{
		free(line);
		free(limiter);
		close(var->pfd[1]);
		exit(0);
	}
	ft_putstr_fd(line, var->pfd[1]);
	here_doc_loop(var, line, limiter);
}

static int	wait_hd_process(t_vars *var, int pid, char *limiter)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		perror("minishell :");
	set_basic_signals();
	if (WIFEXITED(status))
	{
		set_exit_status(WEXITSTATUS(status));
		if (*get_exit_status() == 1)
		{
			free(limiter);
			if (close(var->pfd[1]) == -1)
				perror("minishell");
			if (close(var->pfd[0]) == -1)
				perror("minishell");
			return (1);
		}
	}
	return (0);
}

int	get_hd_input(t_vars *var, char *limiter)
{
	int		pid;

	limiter = ft_strjoin(limiter, "\n", 0);
	if (pipe(var->pfd) == -1)
		perror("minishell");
	pid = fork();
	if (pid == -1)
		perror("minishell");
	if (pid == 0)
		handle_hd_process(var, limiter);
	else
		ignore_signals();
	if (wait_hd_process(var, pid, limiter) == 1)
		return (1);
	read_from_pipe(var, var->i);
	free(limiter);
	return (0);
}
