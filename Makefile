CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = minishell.c

OBJS = $(SRC:.c=.o)

NAME = minishell

RM = rm -f

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re