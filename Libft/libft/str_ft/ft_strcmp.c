/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 11:38:11 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/15 11:44:16 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strcmp(const char *first, const char *second)
{
	while (*first && *second)
	{
		if (*first != *second)
			break ;
		first++;
		second++;
	}
	return ((unsigned char) *first - *second);
}
