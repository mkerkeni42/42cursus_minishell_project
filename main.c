/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/20 14:46:11 by mkerkeni         ###   ########.fr       */
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
	cmd.var = ft_strjoin(cmd.var, "=");
	while (cmd.env[++i])
	{
		if (ft_strnstr(cmd.env[i], cmd.var, ft_strlen(cmd.env[i])))
		{
			if (ft_strnstr(cmd.env[i], cmd.var, ft_strlen(cmd.var)))
			{
				value = cmd.env[i] + ft_strlen(cmd.var) + 1;
				break ;
			}
		}
	}
	if (!value)
		ft_error("ERROR: Variable not found\n");
	return (value);
}
char	*replace_var_by_value(char *s, char *value)
{
	int	i;

	i = -1;
	if (s[0] == '$')
	{
		s[0] = '\0';
		s = ft_strjoin(s, value);
		return (s);	
	}
	while (s[++i])
	{
		if (s[i] == '$')
		{
			s = ft_substr(s, 0, ft_strlen(s) - i + 1);
			s = ft_strjoin(s, value);
		}
	}
	return (s);	
}

char	**get_env_vars(t_command cmd)
{
	char	**args;
	int		i;
	int		j;
	char	*var;
	char	*value;
	
	i = -1;
	j = -1;
	args = ft_split(cmd.cmd_line, ' ');
	while (args[++i])
	{
		j = -1;
		while(args[i][++j])
		{
			if (args[i][j] == '$')
			{
				var = ft_substr(args[i], j + 1, ft_strlen(args[i]) - j);
				cmd.var = var;
				value = get_value_var(cmd);
				args[i] = replace_var_by_value(args[i], value);
			}
		}
	}
	return (args);
}

void	print_str_of_str(char **str)
{
	int	i;
	i = -1;
	while (str[++i])
	{
		ft_printf("%s", str[i]);
		ft_printf(" ");
	}
}
int	main(int ac, char **av, char **env)
{
	t_command	cmd;
	char		**args;
	char		*line;
	
	while (1)
		line = readline("Yamy_shell$");
	cmd.cmd_line = NULL;
	cmd.env = env;
	if (ac > 1)
		cmd.cmd_line = get_cmd_line(av);
	save_history(cmd.cmd_line);
	args = get_env_vars(cmd);
	print_str_of_str(args);
	return (EXIT_SUCCESS);
}
