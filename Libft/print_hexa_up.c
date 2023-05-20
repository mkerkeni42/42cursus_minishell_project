/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa_up.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 10:13:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/12/04 10:37:42 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hexa_up(unsigned long long nb, int count)
{
	char	*base;

	base = "0123456789ABCDEF";
	ft_putnbr_hexa(nb, base);
	while (nb >= 16)
	{
		nb = nb / 16;
		count++;
	}
	count++;
	return (count);
}
