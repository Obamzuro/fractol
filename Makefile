# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 22:45:06 by obamzuro          #+#    #+#              #
#    Updated: 2018/09/29 18:56:43 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCNAME = 	main.c\
			mandelbrot.c

FLAGS = -g -Wall -Wextra -Werror

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

HDRDIR = minilibx_macos		\
		 include

HDR = include/fractol.h

all: lib $(NAME)

$(NAME): $(OBJ) libft/libft.a
	gcc -o $(NAME) $(FLAGS) $(addprefix -I, $(HDRDIR)) -L libft -lft -lmlx -L minilibx_macos -framework OpenGL -framework AppKit $(SRC)

%.o: %.c $(HDR)
	gcc $(FLAGS) $(addprefix -I, $(HDRDIR)) -c $< -o $@

lib:
	make -C libft

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
