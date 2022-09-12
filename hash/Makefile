# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/12 18:26:56 by akoykka           #+#    #+#              #
#    Updated: 2022/09/12 18:27:26 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
SOURCES= hash.c
OBJECTS=$(SOURCES:%.c=%.o)
LIBFT = ../libft/libft.a
INCLUDES = ../libft/includes #-L../libft/ -lft

all: $(OBJECTS) $(LIBFT)

$(OBJECTS): %.o:%.c Makefile
	$(CC) $(CFLAGS) $< -I $(INCLUDES)
	
$(LIBFT):
	make -C ../libft

clean:
	rm -f $(OBJECTS)

fclean: clean

re: fclean all