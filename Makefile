CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c env.c env2.c signals.c

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