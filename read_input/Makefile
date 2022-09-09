# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 12:28:36 by akoykka           #+#    #+#              #
#    Updated: 2022/09/08 12:42:01 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -c -Wall -Wextra -Werror

SRC_LIST =  hash.c read_input.c

OBJECTS = $(SRC_LIST:.c=.o)

LIBFT = ../libft/libft.a

INCLUDES = ../libft/includes #-L../libft/ -lft

all: $(SRC_LIST) Makefile

$(SRC_LIST): $(LIBFT) Makefile
	$(CC) $(CFLAGS) $@ -I $(INCLUDES)

$(LIBFT):
	make -C ../libft



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