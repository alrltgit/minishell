CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c env.c prompt.c

OBJS = $(SRC:.c=.o)

NAME = minishell

RM = rm -f

LDFLAGS = -lreadline
LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) libft.a
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re