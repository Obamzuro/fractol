/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:40:01 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 16:18:00 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H
# define WINWIDTH 1500
# define WINHEIGHT 1500
# define WINSQUARE 2250000
# define AM_INPUT_ARGS_CL 9
# define BUFFER_SIZE_CL 1000
# define KERNEL_SRC "source/drawing.cl"
# include <OpenCL/opencl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

struct s_mlxinfo;

struct s_clinfo;

struct s_fractal;

typedef struct	s_info
{
	struct s_mlxinfo	*mlxinfo;
	struct s_clinfo		*clinfo;
	struct s_fractal	*fractal;
}				t_info;

typedef struct	s_mlxinfo
{
	void				*mlx;
	void				*win;
	void				*img_ptr;
	unsigned char		*img;
	int					size_line;
	int					bits_per_pixel;
	int					endian;
}				t_mlxinfo;

typedef struct	s_clinfo
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_command_queue	queue;
	cl_kernel			kernel;
	cl_mem				inbuffer;
	cl_mem				outbuffer;
}				t_clinfo;

typedef struct	s_fractal
{
	enum				e_fractol_type
	{
		MANDELBROT,
		JULIA,
		BUFFALO,
		BURNING_SHIP,
		TRICORN,
		SIERPINSKI_CARPET
	}					type;
	enum				e_fractol_color
	{
		NORMAL,
		BLUE,
		GREEN,
		RED,
		PSYCHO
	}					colormode;
	int					depth;
	double				reallim[2];
	double				imlim[2];
	double				constant[2];
	int					ismousesensitive : 1;
}				t_fractal;

typedef struct	s_fractal_corr
{
	char					*shortcut;
	enum e_fractol_type		type;
}				t_fractal_corr;

typedef struct	s_pixel
{
	double		x;
	double		y;
	double		z;
}				t_pixel;

void			handle_parameter(t_fractal *fractal, char **argv);

int				ft_mlx_init(t_mlxinfo *mlxinfo);

int				opencl_init(t_clinfo *clinfo);
cl_platform_id	get_platform(void);
cl_device_id	get_device(t_clinfo *cl);
cl_context		get_context(t_clinfo *cl);
char			*load_kernel(const char *name);
cl_program		create_program(char *source, cl_context context);
void			opencl_release(t_clinfo *clinfo);

int				fractal_init(t_fractal *fractal);

int				draw_fractal(t_info *info);

void			scroll_down(int x, int y, t_info *info);
void			scroll_up(int x, int y, t_info *info);
int				change_direction(t_info *info, int keycode);
int				change_depth(t_info *info, int keycode);
int				set_fractal(t_info *info, int keycode);
int				set_color(t_info *info, int keycode);
#endif
