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

SOURCE = main.c

OFILE = $(SOURCE:.c =.o)

NAME = fdf

all: $(NAME)

$(NAME): $(LIBFT) $(OFILE)
	$(CC) $(CFLAGS) $(OFILE) -L minilibx_macos -I minilibx_macos libft/libft.a   -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OFILE): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)    

$(LIBFT):
	make -C ./libft


clean:
	rm -f $(OFILE)

fclean: clean
	rm -f $(NAME)

re: fclean all
