/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 09:55:39 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/12/04 10:36:19 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(unsigned long long nb, char *hexa)
{
	if (nb >= 16)
	{
		ft_putnbr_hexa((nb / 16), hexa);
		ft_putnbr_hexa((nb % 16), hexa);
	}
	else
		ft_putchar_fd(hexa[nb], 1);
}
