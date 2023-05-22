# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/20 09:37:56 by mkerkeni          #+#    #+#              #
#    Updated: 2023/05/22 16:20:13 by mkerkeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
LIBFT	= Libft/
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3

SRCS	=	main.c \
			get_vars.c \
			minishell_utils.c \

OBJS = $(SRCS:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "	Compilation in progress..."
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $^ $(LIBFT)libft.a
	@echo "	Compiled !"

clean:
	@rm -f $(OBJS)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@rm -f Libft/libft.a

re: fclean all

.PHONY: all clean fclean re
