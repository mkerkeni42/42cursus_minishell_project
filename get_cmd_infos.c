/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_infos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 23:00:47 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/30 23:15:19 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_structures(t_cmd *cmd, int stop)
{
	int	i;

	i = -1;
	while (++i <= stop)
		free_tab(cmd[i].args, 0);
	free(cmd);
}

static int	get_args_nb(t_tok *tokens)
{
	int		args_nb;
	t_tok	*tmp;

	args_nb = 0;
	tmp = tokens;
	while (tmp && ft_strcmp(tmp->type, "PIPE"))
	{
		if (!ft_strcmp(tmp->type, "STRING") || !ft_strcmp(tmp->type, "EMPTY"))
			args_nb++;
		tmp = tmp->next;
	}
	return (args_nb);
}

static char	**get_args(t_vars *var)
{
	t_tok	*tmp;
	char	**args;
	int		args_nb;
	int		i;

	tmp = var->pipeline;
	args_nb = get_args_nb(tmp);
	args = (char **)ft_malloc(sizeof(char *) * (args_nb + 1));
	i = 0;
	while (tmp && ft_strcmp(tmp->type, "PIPE"))
	{
		if (!ft_strcmp(tmp->type, "STRING") || !ft_strcmp(tmp->type, "EMPTY"))
		{
			args[i] = ft_strdup(tmp->tok);
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

static t_cmd	get_cmd_pipeline(t_vars *var, t_cmd cmd)
{
	cmd.fdin = 0;
	cmd.fdout = 1;
	cmd.pid = 0;
	cmd.args = get_args(var);
	cmd.fdin = get_in_redir(var);
	cmd.fdout = get_out_redir(var);
	while (var->pipeline && ft_strcmp(var->pipeline->type, "PIPE"))
		var->pipeline = var->pipeline->next;
	return (cmd);
}

int	get_cmd_infos(t_vars *var)
{
	t_cmd	*cmd;
	t_tok	*tmp;
	int		i;

	i = -1;
	tmp = var->toks;
	var->pipeline = tmp;
	cmd = (t_cmd *)ft_malloc(sizeof(t_cmd) * (var->pipe_nb + 1));
	while (++i < var->pipe_nb + 1)
	{
		cmd[i] = get_cmd_pipeline(var, cmd[i]);
		if (var->pipeline && var->pipeline->next)
			var->pipeline = var->pipeline->next;
	}
	var->cmd = cmd;
	return (0);
}
