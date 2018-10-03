/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_changers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 18:36:57 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 15:17:16 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		is_setfractal_keycode(int keycode)
{
	if (keycode >= 18 && keycode <= 23)
		return (1);
	return (0);
}

int				set_fractal(t_info *info, int keycode)
{
	if (!is_setfractal_keycode(keycode))
		return (0);
	if (keycode == 18)
		info->fractal->type = MANDELBROT;
	else if (keycode == 19)
		info->fractal->type = JULIA;
	else if (keycode == 20)
		info->fractal->type = BUFFALO;
	else if (keycode == 21)
		info->fractal->type = BURNING_SHIP;
	else if (keycode == 23)
		info->fractal->type = TRICORN;
	else if (keycode == 22)
		info->fractal->type = SIERPINSKI_CARPET;
	fractal_init(info->fractal);
	draw_fractal(info);
	return (1);
}
