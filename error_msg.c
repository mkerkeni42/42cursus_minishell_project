/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:24:36 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/19 12:34:21 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_error_message(char *error, int x)
{
	char	*error_msg;

	error_msg = NULL;
	if (x == 0)
		error_msg = get_bad_tok_err(error, error_msg);
	else if (x == 1)
		error_msg = get_syntax_err(error, error_msg);
	else if (x == 2)
		error_msg = get_quote_error(error_msg);
	else if (x == 3)
		error_msg = get_file_error(error, error_msg);
	else if (x == 4)
		error_msg = get_cmd_error(error, error_msg);
	else if (x == 5)
		error_msg = get_exit_error(error, error_msg);
	else if (x == 6)
		error_msg = get_mult_arg_err("exit: ", error_msg);
	else if (x == 7)
		error_msg = get_ambig_err(error, error_msg);
	else if (x == 8)
		error_msg = get_dir_error(error, error_msg);
	else if (x == 9)
		error_msg = get_var_name_err(error, error_msg);
	handle_error(error_msg, 0);
}

void	handle_error(char *message, int x)
{
	if (x == 1)
		perror(message);
	else if (x == 0)
		ft_putstr_fd(message, 2);
	free(message);
}

void	get_fct_error(void)
{
	perror("minishell");
	set_exit_status(EXIT_FAILURE);
	exit(*(get_exit_status()));
}
