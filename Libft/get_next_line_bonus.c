/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:54:14 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/02/23 14:13:19 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*trim_buf(char	*buf, char *final, char *temp)
{
	int		i;
	char	*after_nl;
	char	*before_nl;

	i = 0;
	while (buf[i] != *(ft_strchr(buf, '\n')))
		i++;
	before_nl = ft_substr(buf, 0, i + 1);
	after_nl = ft_substr(buf, i + 1, ft_strlen(buf) - i);
	final = ft_strjoin_gnl(final, before_nl, 1);
	ft_strcpy(temp, after_nl);
	free(after_nl);
	return (final);
}

static char	*trim_temp(char *temp, char *final)
{
	int		i;
	char	*after_nl;
	char	*before_nl;

	i = 0;
	while (temp[i] != *(ft_strchr(temp, '\n')))
		i++;
	before_nl = ft_substr(temp, 0, i + 1);
	after_nl = ft_substr(temp, i + 1, ft_strlen(temp) - i);
	final = ft_strjoin_gnl(final, before_nl, 1);
	ft_strcpy(temp, after_nl);
	free(after_nl);
	return (final);
}

static char	*handle_error(char *final, char *temp, int bool)
{
	free(final);
	if (bool == 1)
		final = NULL;
	temp[0] = '\0';
	return (NULL);
}

char	*handle_buf(char *buf, char *temp, char *final)
{
	if (ft_strchr(buf, '\n') != 0)
		final = trim_buf(buf, final, temp);
	else
		final = ft_strjoin_gnl(final, buf, 0);
	return (final);
}

char	*get_next_line(int fd)
{
	t_lst		var;
	static char	temp[1024][(BUFFER_SIZE + 1)];

	var.ret = 1;
	var.buf[0] = '\0';
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	var.final = malloc(sizeof(char));
	var.final[0] = '\0';
	if (ft_strchr(temp[fd], '\n') != 0 && *temp[fd])
		return (trim_temp(temp[fd], var.final));
	var.final = ft_strjoin_gnl(var.final, temp[fd], 0);
	while (var.ret != 0 && ft_strchr(var.buf, '\n') == 0)
	{
		var.ret = read(fd, var.buf, BUFFER_SIZE);
		if (var.ret == -1)
			return (handle_error(var.final, temp[fd], 0));
		var.buf[var.ret] = '\0';
		var.final = handle_buf(var.buf, temp[fd], var.final);
	}
	if (var.ret == 0 && var.final[0] == '\0')
		return (handle_error(var.final, temp[fd], 1));
	else if (var.ret == 0 && ft_strchr(temp[fd], '\n') == 0)
		temp[fd][0] = '\0';
	return (var.final);
}
