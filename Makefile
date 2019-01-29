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
	cc -I minilibx_macos $(SOURCE) -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: all fclean
