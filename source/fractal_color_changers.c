/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_color_changers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:11:02 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 19:44:05 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		set_normal_color(t_info *info)
{
	info->fractal->colormode = 0;
	draw_fractal(info);
}

static void		set_blue_color(t_info *info)
{
	info->fractal->colormode = 1;
	draw_fractal(info);
}

static void		set_green_color(t_info *info)
{
	info->fractal->colormode = 2;
	draw_fractal(info);
}

static void		set_psycho_color(t_info *info)
{
	info->fractal->colormode = 3;
	draw_fractal(info);
}

int				set_color(t_info *info, int keycode)
{
	if (keycode == 6)
	{
		set_normal_color(info);
		return (1);
	}
	else if (keycode == 7)
	{
		set_blue_color(info);
		return (1);
	}
	else if (keycode == 8)
	{
		set_green_color(info);
		return (1);
	}
	else if (keycode == 9)
	{
		set_psycho_color(info);
		return (1);
	}
	return (0);
}
