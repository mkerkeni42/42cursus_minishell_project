LIBFT_PATH = ./libft/
SRCS_LIBFT = $(addprefix $(LIBFT_PATH), /check_value/ft_isalnum.c \
									/check_value/ft_isascii.c \
									/check_value/ft_isprint.c \
									/check_value/ft_isalpha.c \
									/check_value/ft_isdigit.c \
									/mem_ft/ft_bzero.c \
									/mem_ft/ft_memset.c \
									/mem_ft/ft_memcpy.c \
									/mem_ft/ft_memmove.c \
									/mem_ft/ft_memcmp.c \
									/mem_ft/ft_memchr.c \
									/mem_ft/ft_calloc.c \
									/str_ft/ft_strlen.c \
									/str_ft/ft_toupper.c \
									/str_ft/ft_tolower.c \
									/str_ft/ft_strlcpy.c \
									/str_ft/ft_strlcat.c \
									/str_ft/ft_strchr.c \
									/str_ft/ft_strrchr.c \
									/str_ft/ft_strdup.c \
									/str_ft/ft_strncmp.c \
									/str_ft/ft_strcmp.c \
									/str_ft/ft_strnstr.c \
									/str_ft/ft_substr.c \
									/str_ft/ft_strjoin.c \
									/str_ft/ft_strtrim.c \
									/str_ft/ft_striteri.c \
									/str_ft/ft_strmapi.c \
									/str_ft/ft_split.c \
									/convert_ft/ft_atoi.c \
									/convert_ft/ft_itoa.c \
									/printf_ft/ft_putchar_fd.c \
									/printf_ft/ft_putstr_fd.c \
									/printf_ft/ft_putendl_fd.c \
									/printf_ft/ft_putnbr_fd.c \
									/lst_ft/ft_lstnew.c \
									/lst_ft/ft_lstadd_back.c \
									/lst_ft/ft_lstsize.c \
									/lst_ft/ft_lstlast.c \
									/lst_ft/ft_lstadd_front.c \
									/lst_ft/ft_lstdelone.c \
									/lst_ft/ft_lstiter.c \
									/lst_ft/ft_lstclear.c \
									/lst_ft/ft_lstmap.c)

FT_PRINTF_PATH = ./ft_printf/
SRCS_FT_PRINTF = $(addprefix $(FT_PRINTF_PATH), ft_char.c \
												ft_nbr.c \
												ft_printf.c)

GNL_PATH = ./get_next_line/
SRCS_GNL = $(addprefix $(GNL_PATH), get_next_line.c \
									get_next_line_utils.c)

OBJS = $(SRCS_LIBFT:.c=.o) $(SRCS_FT_PRINTF:.c=.o) $(SRCS_GNL:.c=.o)

NAME = libft.a
all : $(NAME)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

.c.o:
	@$(CC) $(CFLAGS) -c -I ./inc $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@ar crs $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re