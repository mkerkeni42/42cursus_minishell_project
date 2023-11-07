/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:05:15 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/14 11:54:18 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2, int bool)
{
	char	*str;
	size_t	j;

	j = -1;
	if ((!s1 || !s2) || (!s1 && !s2))
		return (0);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	str = ft_strcpy(str, (char *)s1);
	while (s2[++j])
		str[ft_strlen(s1) + j] = (char)s2[j];
	str[ft_strlen(s1) + j] = '\0';
	if (bool == 1)
		free((char *)s1);
	else if (bool == 2)
	{
		free((char *)s1);
		free((char *)s2);
	}
	else if (bool == 3)
		free((char *)s2);
	return (str);
}
