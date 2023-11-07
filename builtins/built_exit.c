/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/30 16:45:15 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	ft_atol(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

static int	ft_digit(t_data *sh, int c)
{
	if ((c >= '0' && c <= '9') || (sh->bool == 0 && \
		(sh->cmds[1][0] == '-' || sh->cmds[1][0] == '+')))
		return (1);
	return (0);
}

static int	check_long(t_data *sh)
{
	int	i;
	int	sign;

	i = -1;
	sign = 1;
	sh->bool = 0;
	while (sh->cmds[1][++i])
	{
		if (!ft_digit(sh, sh->cmds[1][i]))
			return (1);
		sh->bool = 1;
	}
	if (sh->cmds[1][0] == '-')
		sign = -1;
	if (ft_strlen(sh->cmds[1]) >= 19)
	{
		if ((sign > 0 && ft_strlen(sh->cmds[1]) == 19 && sh->cmds[1][18] < '8') \
			|| (sign < 0 && ft_strlen(sh->cmds[1]) == 20 \
			&& sh->cmds[1][19] < '9'))
			return (0);
		return (1);
	}
	return (0);
}

static void	arg_error(t_data *sh)
{
	long long	new_nb;

	if (check_long(sh) == 1)
	{
		get_error_message(sh->cmds[1], 5);
		return ;
	}
	if (ft_atol(sh->cmds[1]) >= 0)
		set_exit_status(ft_atol(sh->cmds[1]) % 256);
	else
	{
		new_nb = ft_atol(sh->cmds[1]) * -1;
		new_nb %= 256;
		set_exit_status(256 - new_nb);
	}
}

void	built_exit(t_data *sh)
{
	if (sh->exit_pipe != 1)
		printf("exit\n");
	if (arr_size(sh->cmds) == 3)
		arg_error(sh);
	else if (arr_size(sh->cmds) > 3)
	{
		get_error_message(NULL, 6);
		return ;
	}
	if (sh->exit_pipe != 1)
		exit(*get_exit_status());
}
