/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:16:52 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/22 16:21:33 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_var_by_value(char *s, char *value)
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
			s = ft_substr(s, 0, ft_strlen(s) - (ft_strlen(s) - i));
			s = ft_strjoin(s, value);
		}
	}
	return (s);	
}

static char	*get_value_var(t_command cmd)
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
