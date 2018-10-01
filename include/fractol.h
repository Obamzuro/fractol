/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:40:01 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/30 13:46:06 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H
# define WINWIDTH 1500
# define WINHEIGHT 1500
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

struct				s_fractal;

typedef struct		s_info
{
	void				*mlx;
	void				*win;
	void				*img_ptr;
	unsigned char		*img;
	int					size_line;
	struct s_fractal	*fractal;
}					t_info;

typedef struct		s_pixel
{
	double		x;
	double		y;
	double		z;
}					t_pixel;

typedef struct		s_fractal
{
	int		depth;
	double	reallim[2];
	double	imlim[2];
}					t_fractal;

void		draw_mandelbrot(t_info *info);
int			set_intensity_on(int red,
		int green, int blue, double change);
#endif
