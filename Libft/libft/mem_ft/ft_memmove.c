/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:45:39 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/05 13:05:30 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dstcpy;
	unsigned const char	*srcpy;
	size_t				i;

	i = 0;
	dstcpy = (unsigned char *)dest;
	srcpy = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	if (src < dest)
	{
		while (n--)
			dstcpy[n] = srcpy[n];
	}
	else
	{
		while (i < n)
		{
			dstcpy[i] = srcpy[i];
			i++;
		}
	}
	return (dest);
}
