/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_changers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:36:57 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 20:39:00 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		set_mandelbrot(t_info *info)
{
	info->fractal->type = MANDELBROT;
	fractal_init(info->fractal);
	draw_fractal(info);
}

static void		set_julia(t_info *info)
{
	info->fractal->type = JULIA;
	fractal_init(info->fractal);
	draw_fractal(info);
}

static void		set_sierpinski(t_info *info)
{
	info->fractal->type = SIERPINSKI_CARPET;
	fractal_init(info->fractal);
	draw_fractal(info);
}

int				set_fractal(t_info *info, int keycode)
{
	if (keycode == 18)
	{
		set_mandelbrot(info);
		return (1);
	}
	else if (keycode == 19)
	{
		set_julia(info);
		return (1);
	}
	else if (keycode == 20)
	{
		set_sierpinski(info);
		return (1);
	}
	return (0);
}
