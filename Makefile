# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkorsako <pkorsako@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/04 15:03:37 by pkorsako          #+#    #+#              #
#    Updated: 2023/02/10 18:41:09 by pkorsako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

PHILO_SRC = philo_life.c philosopher.c
PHILO_OBJ = $(PHILO_SRC:.c=.o)


CC = cc
CFLAGS = -g -pthread#-fsanitize=address #-Wall -Wextra -Werror

HEADER_SRC = philosopher.h

%.o: %.c $(HEADER_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(PHILO_OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean:
	rm -f $(PHILO_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
