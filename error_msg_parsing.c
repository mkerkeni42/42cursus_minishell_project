/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:43:46 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/06 12:34:24 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bad_tok_err(char *error, char *err_msg)
{
	char	*begin;
	char	*end;

	set_exit_status(1);
	begin = "minishell: ";
	end = ": undefined token\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

char	*get_syntax_err(char *error, char *err_msg)
{
	char	*begin;
	char	*end;

	set_exit_status(2);
	begin = "minishell: ";
	end = "syntax error near unexpected token `";
	err_msg = ft_strjoin(begin, end, 0);
	err_msg = ft_strjoin(err_msg, error, 1);
	err_msg = ft_strjoin(err_msg, "\'\n", 1);
	return (err_msg);
}

char	*get_quote_error(char *err_msg)
{
	char	*end;
	char	*begin;

	set_exit_status(1);
	begin = "minishell: ";
	end = "syntax error: expecting closing quote\n";
	err_msg = ft_strjoin(begin, end, 0);
	return (err_msg);
}

char	*get_ambig_err(char *error, char *err_msg)
{
	char	*begin;
	char	*end;

	set_exit_status(1);
	begin = "minishell: ";
	end = ": Ambigous redirection\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

char	*get_var_name_err(char *error, char *err_msg)
{
	char	*export_msg;
	char	*begin;
	char	*end;

	set_exit_status(1);
	export_msg = "export: ";
	begin = "minishell: ";
	end = ": not a valid identifier\n";
	err_msg = ft_strjoin(begin, export_msg, 0);
	err_msg = ft_strjoin(err_msg, error, 1);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}
