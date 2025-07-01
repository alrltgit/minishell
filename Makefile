CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c env.c env2.c signals.c free.c free_utils.c \
builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c \
builtins/ft_echo.c builtins/ft_export.c builtins/ft_exit.c \
builtins/ft_unset.c expand/expander.c \
parse_input/find_cmd.c parse_input/utils.c parse_input/utils_2.c parse_input/utils_3.c parse_input/utils_4.c \
parse_input/utils_5.c parse_input/utils_6.c parse_input/utils_7.c \
parse_input/find_flags.c \
parse_input/find_args.c parse_input/find_args_utils.c parse_input/find_args_v2.c \
parse_input/fill_unit_linked_list.c parse_input/parse_input.c \
parse_input/parse_input_utils.c parse_input/split_readline.c \
parse_input/split_readline_utils.c \
exec/exec_utils.c exec/exec_utils_1.c exec/exec.c exec/helpers.c \
piping/piping.c piping/piping_utils.c \
redirection/redirection.c redirection/heredoc.c redirection/append.c \
parse_input/handle_quotes.c builtins/ft_export_utils.c expand/expander_utils.c\

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