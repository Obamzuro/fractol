/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:59:05 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 21:23:38 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		button_up(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->imlim[0] -= 0.05 * scale;
	info->fractal->imlim[1] -= 0.05 * scale;
	draw_fractal(info);
}

void		button_down(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->imlim[0] += 0.05 * scale;
	info->fractal->imlim[1] += 0.05 * scale;
	draw_fractal(info);
}

void		button_left(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->reallim[0] -= 0.05 * scale;
	info->fractal->reallim[1] -= 0.05 * scale;
	draw_fractal(info);
}

void		button_right(t_info *info)
{
	double		scale;

	scale = (info->fractal->reallim[1] - info->fractal->reallim[0]) / 4;
	info->fractal->reallim[0] += 0.05 * scale;
	info->fractal->reallim[1] += 0.05 * scale;
	draw_fractal(info);
}
