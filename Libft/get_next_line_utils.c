/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 09:38:50 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/02/23 14:02:04 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int		i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	if (c == '\0')
		return (s + s_len);
	return (0);
}*/

/*char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	str = NULL;
	i = 0;
	if (start > ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if (len <= ft_strlen(s))
		str = malloc(sizeof(char) * (len + 1));
	else
		str = malloc(sizeof(char) * (ft_strlen(s) - start));
	if (!str)
		return (NULL);
	while (s[start] && start < ft_strlen(s) && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}*/

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int x)
{
	char	*str_final;
	int		i;
	int		len_final;

	i = 0;
	len_final = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	str_final = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str_final)
		return (NULL);
	else
	{
		ft_strcpy(str_final, s1);
		while (s2[i] != '\0')
		{
			str_final[i + ft_strlen(s1)] = s2[i];
			i++;
		}
		str_final[len_final] = '\0';
	}
	free (s1);
	if (x == 1)
		free (s2);
	return (str_final);
}
