
#-------------------COLORS------------------#
DEF = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
RED = \033[31;2m
BLACK = \033[38;5;238m
BLUE = \033[38;5;153m
GREEN = \033[38;5;48m
YELLOW = \033[38;5;226m
ORANGE = \033[38;5;202m
PINK = \033[38;5;198m
PURPLE = \033[38;5;147m
UP = UP = \033[A

#-------------------SRCS--------------------#
SRCS	=	main.c \
			minishell_utils.c \
			error_msg.c \
			error_msg_parsing.c \
			error_msg_exec.c \
			exit_status.c \
			./lexer/lst_functions.c \
			./lexer/get_token.c \
			./lexer/check_token.c \
			./lexer/get_token_type.c \
			./lexer/handle_chevrons.c \
			./parser/parsing.c \
			./parser/get_string_type.c \
			./expander/here_doc.c \
			./expander/here_doc_process.c \
			./expander/handle_limiter.c \
			./expander/lst_functions_2.c \
			./expander/expand_quotes.c \
			./expander/empty_token.c \
			./expander/get_vars.c \
			./expander/get_value.c \
			./parser/pipe_check.c \
			get_cmd_infos.c \
			get_redirections.c \
			./execution/processes.c \
			./execution/check_exec_file.c \
			./execution/set_redirections.c \
			./execution/handle_empty_pipe.c \
			./execution/execution.c \
			./execution/exec_builtin.c \
			./builtins/built_exit.c \
			./builtins/built_echo.c \
			./builtins/built_export.c \
			./builtins/built_export_var.c \
			./builtins/export_var_utils.c \
			./builtins/built_unset.c \
			./builtins/built_unset_utils.c \
			./builtins/built_utils.c \
			./builtins/update_vars.c \
			signal.c

OBJS = $(SRCS:.c=.o)

#------------------COMPILE------------------#
CC = gcc
CFLAGS = -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS += -fsanitize=address -g3
endif

.c.o:
	@$(CC) $(CFLAGS) -c -I ./inc/ $< -o $(<:.c=.o)

#------------------RULES---------------------#
NAME = minishell

all : $(NAME)

$(NAME): $(OBJS)
	@echo ""
	@echo "	$(BOLD)$(PINK)$(UNDERLINE)Compiling...$(DEF)  $(PURPLE)$(BOLD)Minishell$(DEF) ⏳"
	@$(MAKE) -C ./Libft/
	@$(CC) $(CFLAGS) $(OBJS) -L$(shell brew --prefix readline)/lib -lreadline ./Libft/libft.a -o $(NAME)
	@clear
	@echo "	$(YELLOW)$(BOLD)Compiled ! ✨$(DEF)"

debug: fclean
	@$(MAKE) DEBUG=1

clean:
	@$(MAKE) clean -C ./Libft/
	@rm -rf $(OBJS)
	@echo "	❌ $(BOLD)$(RED)Deleted file .o$(DEF)"

fclean: clean
	@rm -rf ./Libft/libft.a
	@rm -rf $(NAME)
	@echo "	❌ $(BOLD)$(RED)Deleted file .a$(DEF)"

re: fclean all

.PHONY: all clean fclean re debug
