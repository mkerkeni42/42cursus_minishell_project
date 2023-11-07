/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:20:22 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/30 14:21:27 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_limiter(t_vars *var)
{
	t_tok	*tmp;
	int		i;

	tmp = var->toks;
	var->data = (t_input **)ft_malloc(sizeof(t_input *) * (var->pipe_nb + 2));
	init_data(var);
	i = 0;
	if (handle_here_doc(var, tmp, i))
		return (1);
	return (0);
}

t_tok	*remove_quotes_limiter(t_tok *tmp)
{
	int		i;
	char	*before_quote;
	char	*after_quote;
	char	*new_tok;

	i = 0;
	new_tok = ft_strdup(tmp->tok);
	while (new_tok[i])
	{
		if (new_tok[i] == '\"' || new_tok[i] == '\'')
		{
			before_quote = ft_substr(new_tok, 0, i);
			after_quote = ft_substr(new_tok, i + 1, ft_strlen(new_tok) - i);
			free(new_tok);
			new_tok = ft_strjoin(before_quote, after_quote, 2);
			i = 0;
		}
		else
			i++;
	}
	ft_strcpy(tmp->tok, new_tok);
	free(new_tok);
	return (tmp);
}
