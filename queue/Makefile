CC = gcc
CFLAGS = -g -c -Wall -Wextra -Werror
SOURCES=queue.c
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
