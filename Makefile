# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleblond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 16:44:12 by jleblond          #+#    #+#              #
#    Updated: 2019/01/15 16:44:14 by jleblond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Werror -Wextra

SOURCE = main.c \

NAME = fdf

all: $(NAME)

$(NAME):
	cc -I minilibx $(SOURCE) -L minilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)