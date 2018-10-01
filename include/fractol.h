/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:40:01 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/01 22:04:56 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FDF_H
# define __FDF_H
# define WINWIDTH 1500
# define WINHEIGHT 1500
# include <OpenCL/opencl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

struct				s_fractal;

struct				s_clinfo;

typedef struct		s_info
{
	void				*mlx;
	struct s_clinfo		*cl;
	void				*win;
	void				*img_ptr;
	unsigned char		*img;
	int					size_line;
	struct s_fractal	*fractal;
}					t_info;

typedef struct			s_clinfo
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_command_queue	queue;
	cl_kernel			kernel;
}					t_clinfo;

typedef struct		s_pixel
{
	double		x;
	double		y;
	double		z;
}					t_pixel;

typedef struct		s_fractal
{
	enum		e_fractol_type
	{
		MANDELBROT
	}		type;
	int		depth;
	double	reallim[2];
	double	imlim[2];
}					t_fractal;

int			draw_fractal(t_info *info);
int			set_intensity_on(int red,
		int green, int blue, double change);
int			opencl_init(t_clinfo *clinfo);
#endif
