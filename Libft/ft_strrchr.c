/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:59:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/11/20 11:42:06 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;
	size_t	s_len;

	i = 0;
	ptr = (char *)s;
	s_len = ft_strlen(s);
	i = s_len;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return (ptr + i);
		i--;
	}
	if (c == '\0')
		return (ptr + s_len);
	return (0);
}
