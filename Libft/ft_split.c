/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 12:24:24 by mkerkeni          #+#    #+#             */
/*   Updated: 2022/11/28 14:30:26 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			while (s[i] && s[i] != c)
			i++;
		count++;
		}
	}
	return (count);
}

typedef struct s_split {
	char	**final;
	int		i;
	int		j;
	int		count;
}	t_split;

int	incr(char const *s, char c, int i)
{
	while (s[i] == c && s[i])
		i++;
	return (i);
}

int	incr_word(char const *s, char c, int i, int count)
{
	while (s[i + count] != c && s[i + count])
		count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	t_split	vs;

	vs.j = 0;
	vs.i = 0;
	vs.count = 0;
	if (!s)
		return (NULL);
	vs.final = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!vs.final)
		return (0);
	while (s[vs.i])
	{
		vs.i = incr(s, c, vs.i);
		vs.count = incr_word(s, c, vs.i, vs.count);
		if (vs.count > 0)
		{
			vs.final[vs.j++] = ft_substr(s, vs.i, vs.count);
			if (!vs.final[vs.j - 1])
				return (0);
			vs.i += vs.count;
			vs.count = 0;
		}
	}
	vs.final[vs.j] = NULL;
	return (vs.final);
}
