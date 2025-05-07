CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c env.c env2.c signals.c \
builtins/ft_pwd.c builtins/ft_env.c \
prompt.c \
parse_input/split_read_line.c \
parse_input/find_cmd.c parse_input/utils.c parse_input/find_flags.c \
parse_input/find_args.c parse_input/fill_unit_linked_list.c parse_input/parse_input.c

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