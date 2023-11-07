/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_empty_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:30 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/01 14:55:22 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_null_stdout(void)
{
	int		null_fd;

	null_fd = open("/dev/null", O_WRONLY);
	dup2(null_fd, STDOUT_FILENO);
	close(null_fd);
}

void	read_stdin(void)
{
	int		tmp_fd[2];
	char	*input;
	char	*new_input;

	pipe(tmp_fd);
	input = get_next_line(0);
	if (!input)
		exit(*get_exit_status());
	new_input = ft_substr(input, 0, ft_strlen(input) - 1);
	free(input);
	write(tmp_fd[1], new_input, ft_strlen(new_input));
	free(new_input);
	close(tmp_fd[1]);
	dup2(tmp_fd[0], STDIN_FILENO);
	close(tmp_fd[0]);
}

int	is_empty_pipe(int fd)
{
	char	buf[1];
	int		ret;

	ret = read(fd, buf, sizeof(buf));
	if (ret == 0)
		return (1);
	return (0);
}

void	close_pipes(t_vars *var, int *pfd, int i)
{
	if (i)
		if (close(var->tmp_fd) == -1)
			perror("minishell");
	if (var->cmd[i].fdin == -2)
		if (close(var->here_doc[0]) == -1)
			perror("minishell");
	if (close(pfd[1]) == -1)
		perror("minishell");
}

int	check_only_empty_pipes(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->pipe_nb + 1 && var->cmd[i].args)
	{
		if (var->cmd[i].args[0]
			&& (ft_strcmp(var->cmd[i].args[0], "cat") || var->cmd[i].args[1]))
			return (1);
		i++;
	}
	return (0);
}
