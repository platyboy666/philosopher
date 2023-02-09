# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 15:03:37 by pkorsako          #+#    #+#              #
#    Updated: 2023/02/07 05:44:01 by pkorsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

PHILO_SRC = philosopher.c
PHILO_OBJ = $(PHILO_SRC:.c=.o)

CC = cc
CFLAGS = -g #-fsanitize=address #-Wall -Wextra -Werror

HEADER_SRC = philosopher.h

all: $(PHILO_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(PHILO_OBJ)

$(NAME): all

%.o: %.c $(HEADER_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PHILO_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
