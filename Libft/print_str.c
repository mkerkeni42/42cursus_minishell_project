/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:53:40 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/12/04 11:25:33 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *str, int count)
{
	if (!str)
		count += write(1, "(null)", 6);
	else
	{
		ft_putstr_fd(str, 1);
		count += ft_strlen(str);
	}
	return (count);
}
