# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 11:42:45 by mkerkeni          #+#    #+#              #
#    Updated: 2023/03/28 11:09:58 by mkerkeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libft.a
CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror
SRCS 	=  ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
		ft_strncmp.c ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strdup.c \
		ft_calloc.c ft_strnstr.c ft_substr.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_strjoin.c ft_strmapi.c ft_striteri.c \
		ft_itoa.c ft_split.c ft_strtrim.c \
		ft_printf.c ft_putnbr_hexa.c ft_putnbr_unsigned_int.c print_hexa_low.c \
		print_hexa_up.c print_nbr.c print_str.c \
		get_next_line.c get_next_line_utils.c get_next_line_bonus.c \
		get_next_line_utils_bonus.c \

OBJS = $(SRCS:.c=.o)

SRCS_BONUS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJS)
	@ar -rcs $@ $^

bonus: $(OBJS_BONUS) $(OBJS)
	@ar -rcs $(NAME) $^
	
clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "	Binary files have been deleted successfully !"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
