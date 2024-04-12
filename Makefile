# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maeferre <maeferre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/17 21:33:49 by maeferre          #+#    #+#              #
#    Updated: 2024/04/12 16:58:35 by maeferre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
STANDARD_FLAGS = -Wall -Wextra -Werror
SRC_DIR = ./src/
SRCS_FILES 		= $(addprefix ${SRC_DIR},\
				main.c				\
				utils.c 			\
				quit_program.c 		\
				ft_strlen.c			\
				ft_split.c 			\
				ft_bzero.c 			\
				ft_strcat.c			\
				ft_strcpy.c			\
				ft_strncmp.c		\
				ft_strchr.c			\
				)
OBJ_FILES = $(SRCS_FILES:%.c=%.o)

all: ${NAME}

$(NAME) : $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES)

%.o : %.c
	$(CC) $(STANDARD_FLAGS) -o $@ -c $<

clean: clean
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: clean all 

.PHONY: all clean fclean re
