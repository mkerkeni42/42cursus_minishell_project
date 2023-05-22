/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/05/22 16:19:14 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
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
	ft_printf("\n");
}
