/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 18:05:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/12/04 12:50:06 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_unsigned_int(unsigned int nb, int count)
{
	ft_putnbr_unsigned_int(nb);
	while (nb >= 10)
	{
		nb = nb / 10;
		count++;
	}
	count++;
	return (count);
}

static int	print_ptr(void *ptr, int count)
{
	unsigned long long	addr;

	addr = (unsigned long long)ptr;
	ft_putstr_fd("0x", 1);
	count += 2;
	ft_putnbr_hexa(addr, "0123456789abcdef");
	while (addr >= 16)
	{
		addr = addr / 16;
		count++;
	}
	count++;
	return (count);
}

static int	manage_format(char format, int count, va_list params)
{
	if (format == 'c')
	{
		ft_putchar_fd(va_arg(params, int), 1);
		count++;
	}
	else if (format == 's')
		count = print_str(va_arg(params, char *), count);
	else if (format == 'p')
		count = print_ptr(va_arg(params, void *), count);
	else if (format == 'd' || format == 'i')
		count = print_nbr(va_arg(params, int), count);
	else if (format == 'u')
		count = print_unsigned_int(va_arg(params, unsigned int), count);
	else if (format == 'x')
		count = print_hexa_low(va_arg(params, unsigned int), count);
	else if (format == 'X')
		count = print_hexa_up(va_arg(params, unsigned int), count);
	else if (format == '%')
		count += write(1, "%", 1);
	return (count);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	params;
	int		count;

	i = 0;
	count = 0;
	va_start(params, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			count = manage_format(s[i + 1], count, params);
			i++;
		}
		else
		{
			write(1, &s[i], 1);
			count++;
		}
		i++;
	}
	va_end(params);
	return (count);
}
