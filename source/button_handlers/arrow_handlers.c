/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:59:05 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 15:24:00 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		button_up(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->imlim[0] -= 0.05 * scale;
	info->fractal->imlim[1] -= 0.05 * scale;
	draw_fractal(info);
}

static void		button_down(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->imlim[0] += 0.05 * scale;
	info->fractal->imlim[1] += 0.05 * scale;
	draw_fractal(info);
}

static void		button_left(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->reallim[0] -= 0.05 * scale;
	info->fractal->reallim[1] -= 0.05 * scale;
	draw_fractal(info);
}

static void		button_right(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->reallim[0] += 0.05 * scale;
	info->fractal->reallim[1] += 0.05 * scale;
	draw_fractal(info);
}

int				change_direction(t_info *info, int keycode)
{
	if (keycode == 13 || keycode == 126)
	{
		button_up(info);
		return (1);
	}
	else if (keycode == 1 || keycode == 125)
	{
		button_down(info);
		return (1);
	}
	else if (keycode == 0 || keycode == 123)
	{
		button_left(info);
		return (1);
	}
	else if (keycode == 2 || keycode == 124)
	{
		button_right(info);
		return (1);
	}
	return (0);
}
