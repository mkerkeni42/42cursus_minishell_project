/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:43:25 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/31 19:06:10 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	basic_signal(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_status(128 + 2);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	command_signal(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_status(128 + 2);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (signal == SIGQUIT)
	{
		set_exit_status(128 + 3);
		ft_putstr_fd("Quit 3\n", STDOUT_FILENO);
	}
	exit(*get_exit_status());
}

void	here_doc_signal(int signal)
{
	if (signal == SIGINT)
	{
		set_exit_status(1);
		printf("\n");
		exit(*get_exit_status());
	}
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	set_basic_signals(void)
{
	set_termios(0);
	signal(SIGINT, basic_signal);
	signal(SIGQUIT, basic_signal);
}
