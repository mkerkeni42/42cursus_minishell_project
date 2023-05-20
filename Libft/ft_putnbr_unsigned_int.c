/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_int.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:54:30 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/02/25 22:05:41 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned_int(unsigned int nb)
{
	if (nb <= 9)
		ft_putchar_fd(nb + '0', 1);
	else
	{
		ft_putnbr_unsigned_int(nb / 10);
		ft_putnbr_unsigned_int(nb % 10);
	}
}
