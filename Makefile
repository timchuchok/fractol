#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/14 08:43:13 by vtymchen          #+#    #+#              #
#    Updated: 2017/02/14 09:05:30 by vtymchen         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	fractol

GCC =	gcc -Wall -Wextra -Werror

FRAMEWORKS =	-framework OpenGL -framework AppKit

HEADER =	fractol.h

SRC = 	main.c \
		julia.c \
		mandel.c \
		serp.c \
		julia_hooks.c \
		mandel_hooks.c \
		serp_hooks.c

OBJ = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)	libx
		gcc -o $(NAME)	-Lminilibx_macos -lmlx $(OBJ) $(FRAMEWORKS)	

%.o: %.c $(HEADER)
		$(GCC) -c -o $@ $<

libx:
		make -C minilibx_macos/

clean:
		rm -f $(OBJ)
		make clean -C minilibx_macos/

fclean: clean
		rm -f $(NAME)

re: fclean all