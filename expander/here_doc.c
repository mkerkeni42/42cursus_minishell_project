/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:59:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/31 17:27:25 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_input(t_vars *var)
{
	t_input	*tmp;
	char	*exp_input;

	var->var = NULL;
	var->value = NULL;
	exp_input = NULL;
	tmp = var->data[var->i];
	while (tmp && tmp->next)
	{
		exp_input = get_var(tmp->input, var, 0, 0);
		tmp->input = ft_strdup(exp_input);
		free(exp_input);
		tmp = tmp->next;
	}
}

void	read_from_pipe(t_vars *var, int i)
{
	t_input	*tmp;
	char	*line;

	if (close(var->pfd[1]) == -1)
		perror("minishell");
	line = get_next_line(var->pfd[0]);
	if (!line)
		return ;
	tmp = ft_lstnew_input(line);
	while (line)
	{
		line = get_next_line(var->pfd[0]);
		ft_lstadd_back_input(&tmp, ft_lstnew_input(line));
	}
	var->data[i] = tmp;
	if (close(var->pfd[0]) == -1)
		perror("minishell");
}

int	handle_here_doc(t_vars *var, t_tok *tmp, int i)
{
	var->i = i;
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "PIPE"))
			var->i++;
		if (!ft_strcmp(tmp->type, "LIMITER"))
		{
			if (ft_strchr(tmp->tok, '\"') || ft_strchr(tmp->tok, '\''))
			{
				tmp = remove_quotes_limiter(tmp);
				if (get_hd_input(var, tmp->tok))
					return (1);
			}
			else
			{
				if (!get_hd_input(var, tmp->tok))
					expand_input(var);
				else
					return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
