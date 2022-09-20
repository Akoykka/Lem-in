# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 12:28:36 by akoykka           #+#    #+#              #
#    Updated: 2022/09/13 18:46:45 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
SOURCES=utils.c read_input.c
OBJECTS=$(SOURCES:%.c=%.o)
LIBFT = ../libft/libft.a
INCLUDES = ../libft/includes #-L../libft/ -lft

all: $(OBJECTS) $(LIBFT) $(HASH)

$(OBJECTS): %.o:%.c Makefile
	$(CC) $(CFLAGS) $< -I $(INCLUDES)
	
$(LIBFT):
	make -C ../libft

$(HASH):
	make -C ../hash
	
clean:
	rm -f $(OBJECTS)

fclean: clean

re: fclean all




#CC=g++
#CFLAGS=-c -Wall
#LDFLAGS=
#SOURCES=main.cpp hello.cpp factorial.cpp
#OBJECTS=$(SOURCES:.cpp=.o)
#EXECUTABLE=hello
#
#all: $(SOURCES) $(EXECUTABLE)
#
#$(EXECUTABLE): $(OBJECTS)
#    $(CC) $(LDFLAGS) $(OBJECTS) -o $@
#
#.cpp.o:
#    $(CC) $(CFLAGS) $< -o $@