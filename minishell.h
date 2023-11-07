/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/11/03 16:55:36 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/inc/libft.h"
# include "Libft/inc/get_next_line.h"
# include "Libft/inc/ft_printf.h"
# include <termios.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define BUFF_SIZE 1000

typedef struct s_input {
	char			*input;
	struct s_input	*next;
}					t_input;

typedef struct s_tok {
	char			*tok;
	char			*type;
	struct s_tok	*next;
	struct s_tok	*prev;
}					t_tok;

typedef struct s_cmd {
	char	**args;
	int		pid;
	int		fdin;
	int		fdout;
}			t_cmd;

typedef struct s_export {
	char	**env;
	char	**exp;
	char	*pre;
	int		j;
}	t_export;

typedef struct s_data {
	t_export	*export;
	char		**env;
	char		**myenv;
	char		**expenv;
	char		**cmds;
	char		*var;
	char		*final;
	char		*line;
	char		**echo;
	int			bool;
	int			exit_pipe;
	int			i;
	int			j;
	int			c;
	int			n;
	int			v;
}				t_data;

typedef struct s_vars {
	char	**my_env;
	t_tok	*toks;
	t_tok	*tok;
	t_tok	*pipeline;
	t_tok	*pipeline_end;
	char	*token;
	char	*start;
	char	*end;
	char	*var;
	char	*value;
	int		len;
	char	*line;
	int		x;
	int		y;
	int		i;
	int		j;
	int		bool;
	int		pipe_nb;
	int		*pids;
	t_input	**data;
	t_cmd	*cmd;
	int		orig_stdin;
	int		orig_stdout;
	int		tmp_fd;
	int		pfd[2];
	int		empty_pipe;
	int		only_empty;
	t_data	*sh;
	int		here_doc[2];
	char	*path;
}			t_vars;

int			main(int ac, char **av, char **env);

void		get_error_message(char *error, int x);
void		handle_error(char *message, int x);
void		get_fct_error(void);

char		*get_var_name_err(char *error, char *err_msg);
char		*get_bad_tok_err(char *error, char *err_msg);
char		*get_syntax_err(char *error, char *err_msg);
char		*get_quote_error(char *err_msg);
char		*get_ambig_err(char *error, char *err_msg);

char		*get_cmd_error(char *error, char *err_msg);
char		*get_exit_error(char *error, char *err_msg);
char		*get_mult_arg_err(char *error, char *err_msg);
char		*get_file_error(char *error, char *err_msg);
char		*get_dir_error(char *error, char *err_msg);

void		print_tab(char **tab);
void		free_tab(char	**tab, int i);
void		init_data(t_vars *var);
void		*ft_malloc(size_t size);
int			check_var_name(char *var);

int			*get_exit_status(void);
void		set_exit_status(int status);
void		wait_for_processes(t_vars *var);
void		set_correct_status(t_vars *var, char **cmds, int i);

void		basic_signal(int signal);
void		command_signal(int signal);
void		here_doc_signal(int signal);
void		ignore_signals(void);
void		set_basic_signals(void);
void		set_termios(int bool);

/*===================================LEXER====================================*/

int			tokenize_line(char *line, t_vars *var);

int			is_special_char(char token);
int			ft_isspace(char token);
int			is_forbidden_char(char token);
int			check_question_mark(t_vars *var, char *line, char *token);
int			check_quote_in_str(t_vars *var, char *start, char *end);

char		*get_double_chevrons_token(t_vars *var);
int			check_chevrons(t_vars *var);
int			is_chevron(char	*token, int x);

char		*get_ex_code_token(t_vars *var);
t_tok		*get_token_type(t_tok *toks);
int			check_spaces(char *line);
int			handle_quote_case(t_vars *var);

t_tok		*ft_lst_new(char *token);
void		ft_lst_add_back(t_tok **lst, t_tok *new);
t_tok		*ft_lst_last(t_tok *lst);
int			ft_lst_size(t_tok *lst);
void		free_list(t_tok **lst, int x);

t_input		*ft_lstnew_input(void *content);
t_input		*ft_lstlast_input(t_input *lst);
void		ft_lstadd_back_input(t_input **lst, t_input *new);
void		print_list_input(t_input *input);
void		free_list_input(t_input **lst, int nb, int x);

void		get_limiter(t_tok *toks);

/*===================================PARSER===================================*/

int			parse_tokens(t_vars *var);

int			check_before_pipe(t_vars *var);
int			get_nb_of_pipes(t_tok *toks);
int			check_double_pipe(t_tok *toks);

void		get_files(t_tok *toks);

/*==================================EXPANDER==================================*/

int			handle_quotes(t_vars *var);

int			check_limiter(t_vars *var);
t_tok		*remove_quotes_limiter(t_tok *tmp);

int			handle_here_doc(t_vars *var, t_tok *tmp, int i);
void		read_from_pipe(t_vars *var, int i);

int			get_hd_input(t_vars *var, char *limiter);

char		*get_var(char *token, t_vars *var, int x, int bool);
char		get_quote_type(char *token);

int			handle_empty_quotes(t_vars *var, char **token);
int			check_if_empty_tok(t_tok *tmp, t_vars *var);
void		handle_value(t_vars *var, int bool);
char		*get_value(t_vars *var);
char		*get_env(t_vars *var, char *variable);
char		*replace_var_by_value(char *line, char *value, int start, int end);

/*==============================REDIRECTIONS==================================*/

int			get_cmd_infos(t_vars *var);
int			get_in_redir(t_vars *var);
int			get_out_redir(t_vars *var);
void		free_structures(t_cmd *cmd, int stop);

/*=============================EXECUTION======================================*/

int			create_processes(t_vars *var, t_data *sh);
void		get_here_doc_input(t_vars *var, int i);

void		get_std_stream(int fd, int std_stream);
void		set_stdin_pipeline(t_vars *var, int *pfd, int tmp_fd, int i);
void		set_stdout_pipeline(t_vars *var, int *pfd, int i);
void		close_files(t_vars *var, int i);

void		close_pipes(t_vars *var, int *pfd, int i);
void		set_null_stdout(void);
void		read_stdin(void);
int			is_empty_pipe(int fd);
int			check_only_empty_pipes(t_vars *var);

int			check_permission(char *file, int x);
int			check_if_dir(char *cmd);
int			exec_cmd(t_vars *var, int i);

int			is_builtin(char *cmd);
void		handle_builtin(t_vars *var, t_data *sh);
void		exec_builtin(t_data *sh);

/*===================================BUILTINS=================================*/

void		my_env(t_data *sh);
void		exp_env(t_data *sh);
int			arr_size(char **array);
void		free_array(t_data *sh);
char		*check_var(char *var);
int			undeclared_var(char **tmp);
void		end_function(t_data *sh, char **tmp, char *var);
void		update_envs(t_data *sh, char **tmp);
void		get_tmp_expenv(t_data *sh, char **tmp);
void		get_tmp_myenv(t_data *sh, char **tmp);

void		built_pwd(void);
void		built_exit(t_data *sh);
void		built_echo(t_data *sh);
void		built_cd(t_data *sh);
void		built_env(t_data *sh);
void		built_unset(t_data *sh);
void		built_export(t_data *sh);
void		export_var(t_data *sh, char *var, int bool);
void		update_shlvl(t_vars *var);
void		update_pwd(t_data *sh);
void		update_oldpwd(t_data *sh);
void		update_underscore(t_vars *var, int i);
void		update_underscore_env(t_data *sh);

extern void	rl_replace_line(const char *text, int clear_undo);
extern void	rl_clear_history(void);

#endif
