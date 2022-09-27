#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoponen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:55:47 by okoponen          #+#    #+#              #
#    Updated: 2022/09/27 14:45:18 by okoponen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME 	= lem_in
LIBFT 	= ./libft
FLAGS   = -Wall -Wextra -Werror
SRC_DIR = srcs/

DEF_COLOR = \033[0;39m
RED = \033[1;91m
GREEN = \033[1;92m

SRC_FILES = hash
SRC_FILES += bfs
SRC_FILES += path_evaluation
SRC_FILES += read_input
SRC_FILES += read_utils

SRC	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ	= $(addsuffix .o, $(SRC_FILES))

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(SRC)
	@ make -C $(LIBFT)
	@ gcc $(FLAGS) -c $(SRC)
	@ gcc -o $(NAME) -Llibft -lft $(OBJ)
	@echo "$(GREEN)lem_in complete$(DEF_COLOR)"

clean :
	@ rm -f $(OBJ)
	@ make clean -C libft/

fclean : clean
	@ rm -f $(NAME)
	@ rm -f $(OBJ)
	@ make fclean -C libft/

re : fclean all
