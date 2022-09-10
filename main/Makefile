# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 11:23:37 by akoykka           #+#    #+#              #
#    Updated: 2022/09/10 11:34:31 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem_in
CC=gcc
CFLAGS= -g -c -Wall -Wextra -Werror
SOURCES= main.c
OBJECTS=$(SOURCES:%.c=%.o)
LIBFT = ../libft/libft.a
INCLUDES = ../libft/includes

all: $(OBJECTS) $(LIBFT)

$(NAME)
	$(CC) $(CFLAGS) $(OBJECTS) -I $(INCLUDES)

$(OBJECTS): %.o:%.c Makefile
	$(CC) $(CFLAGS) $< -I $(INCLUDES)

$(LIBFT):
	make -C ../libft

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
