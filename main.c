/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/20 11:38:57 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

static void	save_history(char *cmd_line)
{
	int	fd;

	fd = open("history", O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		ft_error("ERROR: Failed to open the file\n");
	ft_putstr_fd(cmd_line, fd);
	write(fd, "\n", 1);
}

char	*get_cmd_line(char **av)
{
	char	*cmd_line;
	int		i;
	
	i = 1;
	cmd_line = av[1];
	while (av[++i])
	{
		cmd_line = ft_strjoin(cmd_line, " ");
		cmd_line = ft_strjoin(cmd_line, av[i]);
	}
	return (cmd_line);
}
char	*get_value_var(t_command cmd)
{
	char	*value;
	int		i;

	i = -1;
	value = NULL;
	while (cmd.env[++i])
	{
		if (ft_strnstr(cmd.env[i], cmd.var, ft_strlen(cmd.env[i])))
		{
			value = cmd.env[i] + ft_strlen(cmd.var);
			break ;
		}
	}
	return (value);
}

char	**get_env_vars(t_command cmd)
{
	char	**args;
	int		i;
	char	*var;
	char	*value;
	
	i = -1;
	args = ft_split(cmd.cmd_line, ' ');
	while (args[++i])
	{
		ft_printf("passed here\n");
		if (args[i][0] == '$')
		{
			var = ft_strtrim(args[i], "$");
			value = get_value_var(cmd);
			ft_printf("value = %s\n", value);
		}
	}
	return (args);
}

int	main(int ac, char **av, char **env)
{
	t_command	cmd;
	
	cmd.cmd_line = NULL;
	cmd.env = env;
	if (ac > 1)
		cmd.cmd_line = get_cmd_line(av);
	save_history(cmd.cmd_line);
	get_env_vars(cmd);
	return (EXIT_SUCCESS);
}
