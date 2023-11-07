/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:39:00 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/29 13:47:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include "../inc/get_next_line.h"

char	*ft_strjoingnl(char const *s1, char const *s2, int x)
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
	free((char *)s1);
	if (x == 1)
		free((char *)s2);
	return (str);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_substrgnl(char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (ft_strlen(s) < (int)start)
		return (0);
	if ((int)len <= ft_strlen(s))
		str = malloc(sizeof(char) * (len + 1));
	else
		str = malloc(sizeof(char) * (ft_strlen(s) - start));
	if (!str)
		return (0);
	while (s[start] && (int)start < ft_strlen(s) && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
