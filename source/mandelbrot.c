/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:52:58 by obamzuro          #+#    #+#             */
/*   Updated: 2018/09/30 23:08:42 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calc_depth(t_info *info, double x, double y)
{
	double		real;
	double		im;
	double		nextreal;
	double		nextim;
	int			i;

	x = info->fractal->reallim[0] + (x * (info->fractal->reallim[1]
				- info->fractal->reallim[0]) / WINWIDTH);
	y = info->fractal->imlim[0] + (y * (info->fractal->imlim[1]
				- info->fractal->imlim[0]) / WINHEIGHT);
	real = x;
	im = y;
	i = -1;
	while (++i < info->fractal->depth)
	{
		if (fabs(real * real + im * im) > 4)
			return (i);
		nextreal = real * real - im * im;
		nextim = 2 * real * im;
		real = nextreal + x;
		im = nextim + y;
//		if (fabs(real + im) > 16)
//			return (i);
	}
	return (i);
}

void		draw_mandelbrot(t_info *info)
{
	double	x;
	double	y;
	int		n;

	x = -1;
	while (++x < WINWIDTH)
	{
		y = -1;
		while (++y < WINHEIGHT)
		{
//			if (y == WINHEIGHT / 2 || x == WINWIDTH / 2)
//			{
//				*(info->img + (int)(y * info->size_line + x * 4) + 0) = 0;
//				*(info->img + (int)(y * info->size_line + x * 4) + 1) = 0;
//				*(info->img + (int)(y * info->size_line + x * 4) + 2) = 255;
//				*(info->img + (int)(y * info->size_line + x * 4) + 3) = 0;
//			continue ;
//			}
			n = calc_depth(info, x, y);
			if (n == info->fractal->depth)
				n = 0;
			else
				n = n / (double)info->fractal->depth * 255;
			*(info->img + (int)(y * info->size_line + x * 4) + 0) = n;
			*(info->img + (int)(y * info->size_line + x * 4) + 1) = n;
			*(info->img + (int)(y * info->size_line + x * 4) + 2) = n;
			*(info->img + (int)(y * info->size_line + x * 4) + 3) = 0;
		}
	}
	mlx_put_image_to_window(info->mlx, info->win,
			info->img_ptr, 0, 0);
}
