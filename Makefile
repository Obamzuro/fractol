# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 22:45:06 by obamzuro          #+#    #+#              #
#    Updated: 2018/10/01 22:20:52 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCNAME = 	main.c\
			mandelbrot.c\
			opencl_init.c

FLAGS = -g -Wall -Wextra -Werror

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

HDRDIR = minilibx_macos		\
		 include

HDR = include/fractol.h

all: lib $(NAME)

$(NAME): $(OBJ) libft/libft.a ftprintf/libftprintf.a source/drawing.cl
	gcc -o $(NAME) $(FLAGS) $(addprefix -I, $(HDRDIR)) $(SRC) -L ftprintf -lftprintf -L libft -lft -lmlx -L minilibx_macos -framework OpenGL -framework AppKit -framework OpenCL

%.o: %.c $(HDR)
	gcc $(FLAGS) $(addprefix -I, $(HDRDIR)) -c $< -o $@

lib:
	make -C libft
	make -C ftprintf

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
