# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apple <apple@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 12:57:58 by apple             #+#    #+#              #
#    Updated: 2025/03/31 15:02:49 by apple            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c ft_print_dec.c ft_print_hex_lower.c \
ft_print_hex_upper.c ft_print_pointer.c ft_print_str.c \
ft_print_undec.c ft_strlen_pf.c

OBJS = $(SRC:.c=.o)

NAME = libftprintf.a

CC = cc

RM = rm -f

AR = ar rcs

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS) 
	@$(AR) $(NAME) $(OBJS)

all: $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re