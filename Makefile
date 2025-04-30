CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = minishell.c \
piping/piping.c \
piping/is_command_valid.c \
piping/piping_helpers.c

OBJS = $(SRC:.c=.o)

NAME = minishell

RM = rm -f

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(RM) libft.a
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re