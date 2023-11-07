/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:02:10 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/01 14:28:16 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

void	set_exit_status(int status)
{
	*get_exit_status() = status;
}

void	wait_for_processes(t_vars *var)
{
	int	i;
	int	status;

	i = -1;
	while (++i < var->pipe_nb + 1)
	{
		if (waitpid(var->cmd[i].pid, &status, 0) == -1)
			perror("minishell");
		set_basic_signals();
		if (WIFEXITED(status))
			set_exit_status(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
		{
			if (status == 2)
				printf("\n");
			else if (status == 131)
				printf("Quit 3\n");
			set_exit_status(128 + WTERMSIG(status));
			return ;
		}
	}
	if (close(var->tmp_fd) == -1)
		perror("minishell");
}

void	set_correct_status(t_vars *var, char **cmds, int i)
{
	if (var->cmd[i].args[0][0] == '/')
	{
		get_error_message(cmds[0], 3);
		set_exit_status(127);
	}
	else
		get_error_message(cmds[0], 4);
}

void	set_termios(int bool)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (bool == 0)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
