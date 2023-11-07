/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:43:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/01 14:47:10 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char token)
{
	if (token == '|' || token == '<' || token == '>' || token == '\\'
		|| token == ';' || token == '&' || token == '*' || token == '['
		|| token == ']' || token == '{' || token == '}' || token == '?'
		|| token == '(' || token == ')')
		return (1);
	return (0);
}

int	ft_isspace(char token)
{
	if (token == ' ' || token == '\t' || token == '\n' || token == '\f'
		|| token == '\v' || token == '\r')
		return (1);
	return (0);
}

int	is_forbidden_char(char token)
{
	if (token == '&' || token == '*' || token == ';' || token == '\\'
		|| token == '[' || token == ']' || token == '{' || token == '}'
		|| token == '(' || token == ')')
		return (1);
	return (0);
}

int	check_question_mark(t_vars *var, char *line, char *token)
{
	if (token[0] == '?')
	{
		if (*(line - 1) != '$')
		{
			get_error_message(token, 0);
			var->bool = 1;
			return (1);
		}
	}
	return (0);
}

int	check_quote_in_str(t_vars *var, char *start, char *end)
{
	char	token_type;

	token_type = 0;
	start = var->line;
	end = var->line + 1;
	if (*start == '\"')
	{
		token_type = '\"';
		var->x = 1;
	}
	else if (*start == '\'')
	{
		token_type = '\'';
		var->x = 2;
	}
	start++;
	if (!ft_strchr(start, token_type))
	{
		get_error_message(NULL, 2);
		return (var->x);
	}
	while (*end && *end != token_type)
		end++;
	end++;
	return (0);
}
