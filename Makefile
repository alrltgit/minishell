CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c env.c env2.c signals.c free.c \
builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c \
builtins/ft_echo.c builtins/ft_export.c prompt.c \
parse_input/split_read_line.c \
parse_input/find_cmd.c parse_input/utils.c parse_input/find_flags.c \
parse_input/find_args.c parse_input/fill_unit_linked_list.c parse_input/parse_input.c \
exec/exec_utils.c exec/exec.c exec/helpers.c \
piping/piping.c redirection/redirection.c

OBJS = $(SRC:.c=.o)

NAME = minishell

RM = rm -f

LDFLAGS = -lreadline
LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re