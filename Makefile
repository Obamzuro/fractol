# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 22:45:06 by obamzuro          #+#    #+#              #
#    Updated: 2018/10/02 19:16:05 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRCNAME = 	main.c\
			opencl_init.c\
			opencl_init2.c\
			mlx_init.c\
			fractal_init.c\
			draw_fractal.c\
			scroll_handlers.c\
			arrow_handlers.c\
			depth_handlers.c\
			fractal_changers.c\
			fractal_color_changers.c

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
