# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynieto-s <ynieto-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/20 20:22:45 by ynieto-s          #+#    #+#              #
#    Updated: 2025/09/29 14:11:44 by ynieto-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/main.c \
          src/philo.c \
          src/utils.c

OBJ     = $(SRC:.c=.o)
INCLUDES = -Iinc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re