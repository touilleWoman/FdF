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

SOURCE = main.c stock_map.c 

OFILE = $(SOURCE:.c=.o)

NAME = fdf

LIBFT = libft/libft.a

all: $(NAME)

$(NAME):  $(OFILE)
	$(CC) $(CFLAGS) $(OFILE)   libft/libft.a  -L minilibx_macos   -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OFILE): $(SOURCE) $(LIBFT)
	$(CC) $(CFLAGS) -c $(SOURCE)  -I minilibx_macos

$(LIBFT):
	make -C ./libft

clean:
	rm -f $(OFILE)

fclean: clean
	rm -f $(NAME)

re: fclean all