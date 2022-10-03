# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/27 13:55:47 by okoponen          #+#    #+#              #
#    Updated: 2022/09/28 16:52:43 by okoponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= lem-in
LIBFT 	= ./libft
FLAGS   = -Wall -Wextra -Werror -g
SRC_DIR = srcs/

DEF_COLOR = \033[0;39m
RED = \033[1;91m
GREEN = \033[1;92m

SRC_FILES = hash
SRC_FILES += read_input
SRC_FILES += lem_in
SRC_FILES += queue
SRC_FILES += read_utils
SRC_FILES += debug

SRC	= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ	= $(addsuffix .o, $(SRC_FILES))

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(SRC) Makefile
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
