/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/31 19:09:43 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_vars(char *line, t_vars *var, int x)
{
	free(line);
	if (x == 1)
		free_structures(var->cmd, var->pipe_nb);
	free_list_input(var->data, var->pipe_nb, 0);
	free_list(&(var->toks), 0);
	free(var);
}

static void	init_var(t_vars *var, t_data *sh)
{
	var->toks = NULL;
	var->token = NULL;
	var->data = NULL;
	var->bool = 0;
	var->y = 0;
	var->j = 0;
	var->sh = sh;
}

static t_vars	*readline_loop(t_vars *var, char *line, t_data *sh)
{
	while (1)
	{
		var = (t_vars *)ft_malloc(sizeof(t_vars));
		init_var(var, sh);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			free_vars(line, var, 0);
			set_exit_status(0);
			exit(*get_exit_status());
		}
		if (*line)
			add_history(line);
		if (tokenize_line(line, var))
			free_vars(line, var, 0);
		else if (get_cmd_infos(var))
			free_vars(line, var, 0);
		else if (create_processes(var, sh))
			free_vars(line, var, 1);
		else
			free_vars(line, var, 1);
	}
	return (var);
}

static void	check_args(int ac, char **av, char **env)
{
	if (ac != 1)
	{
		get_error_message(av[1], 3);
		if (ac > 2)
		{
			set_exit_status(127);
			exit(*get_exit_status());
		}
		set_exit_status(1);
		exit(*get_exit_status());
	}
	else if (!env[0])
	{
		ft_putstr_fd("minishell: the environment is empty\n", 2);
		set_exit_status(1);
		exit(*get_exit_status());
	}
}

int	main(int ac, char **av, char **env)
{
	static char			*line;
	t_vars				*var;
	t_data				sh;

	set_exit_status(EXIT_SUCCESS);
	var = NULL;
	check_args(ac, av, env);
	sh.env = env;
	my_env(&sh);
	exp_env(&sh);
	set_basic_signals();
	var = readline_loop(var, line, &sh);
	set_termios(1);
	return (EXIT_SUCCESS);
}
