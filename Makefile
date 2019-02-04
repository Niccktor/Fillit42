# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbeguin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/06 12:23:45 by tbeguin           #+#    #+#              #
#    Updated: 2019/02/04 20:36:03 by msaubin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

CC = gcc

CFLAGS = -Wall -Werror -Wextra

LIB_FT		= libft
FT_LNK		= -L $(LIB_FT) -l ft

SRC = main.c		\
	  util.c		\
	  util_2.c		\
	  read.c		\
	  tetrimino.c	\
	  solve.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -I $(LIB_FT) -I ./ -c $< -o $@
	@echo "\033[36m$(CC) $(CFLAGS) -c $< -o $@\033[0m"

LIB :
	@make -C libft/

$(NAME) : LIB $(OBJ)
	@$(CC) $(CFLAGS) $(FT_LNK) $(OBJ) -o $(NAME)
	@echo "\033[32m$(NAME) Created\033[0m"
 
clean : cleanlib
	@rm -f $(OBJ)
	@echo "\033[31mRemoved obj files\033[0m"

fclean : fcleanlib clean
	@rm -f $(NAME)
	@echo "\033[31mRemoved $(NAME)\033[0m"

re : fclean all

cleanlib :
	@make -C $(LIB_FT) clean

fcleanlib :
	@make -C $(LIB_FT) fclean

.PHONY: make clean fclean re all cleanlib fcleanlib
