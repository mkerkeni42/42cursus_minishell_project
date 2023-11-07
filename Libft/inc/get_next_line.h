/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:39:03 by ykifadji          #+#    #+#             */
/*   Updated: 2023/03/28 11:42:45 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*get_l(char *temp, char *final, char *buf, int ret);
char	*trim_temp(char *temp, char *final);
char	*trim_buf(char *temp, char *final, char *buf);
char	*ft_error(char *final, char *temp);

char	*ft_strcpy(char *dest, char *src);
char	*ft_strjoingnl(char const *s1, char const *s2, int x);
char	*ft_substrgnl(char *s, unsigned int start, size_t len);

#endif