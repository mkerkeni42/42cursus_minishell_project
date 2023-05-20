/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:13:43 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/11/24 15:47:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*return_empty(char *str)
{
	str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	char		*str;

	i = 0;
	j = 0;
	str = NULL;
	if (!s1 || !set)
		return (NULL);
	if (s1[0] == 0)
		return (return_empty(str));
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	if (i == ft_strlen(s1))
		return (return_empty(str));
	j = i;
	i = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i--;
	str = malloc (sizeof(char) * (i - j + 2));
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[j], i - j + 2);
	return (str);
}
