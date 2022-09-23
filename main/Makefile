# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 11:23:37 by akoykka           #+#    #+#              #
#    Updated: 2022/09/23 14:43:00 by akoykka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=lem_in
CC=gcc
FLAGS= -g -o $(NAME) -Wall -Wextra -Werror
CFLAGS= -g -c -Wall -Wextra -Werror
SOURCES= lem_in.c read_input.c path_evaluation.c
SOURCES+= debug.c
OBJECTS=$(SOURCES:%.c=%.o)

LIBFT = ../libft/libft.a
QUEUE = ../queue/queue.a
HASH =  ../hash/hash.a

LIBRARIES = -L../libft/ -lft -L../queue/ -lqueue -L../hash/ -lhash

INCLUDES = -I ../libft/includes

all: $(FT) $(NAME)

$(NAME): $(OBJECTS) $(QUEUE) $(HASH) Makefile
	$(CC) $(FLAGS) $(OBJECTS) $(INCLUDES) $(LIBRARIES)

$(OBJECTS): %.o:%.c Makefile
	$(CC) $(CFLAGS) $< $(INCLUDES)
	

$(LIBFT):
	make -C ../libft

$(QUEUE):
	make -C ../queue
	
$(HASH):
	make -C ../hash

clean:
	rm -f $(OBJECTS)
	make clean -C  ../hash
	make clean -C  ../queue
	make clean -C  ../libft

fclean: clean
	rm -f $(NAME)
	make fclean -C  ../hash
	make fclean -C  ../queue
	make fclean -C  ../libft

re: fclean all