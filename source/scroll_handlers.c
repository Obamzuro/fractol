/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:54:56 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 22:39:45 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		scroll_down(int x, int y, t_info *info)
{
	double		realpos;
	double		impos;

	realpos = info->fractal->reallim[0] + (x * (info->fractal->reallim[1]
				- info->fractal->reallim[0]) / WINWIDTH);
	impos = info->fractal->imlim[0] + (y * (info->fractal->imlim[1]
				- info->fractal->imlim[0]) / WINHEIGHT);
	info->fractal->reallim[0] = realpos -
		((realpos - info->fractal->reallim[0]) * 0.95);
	info->fractal->reallim[1] = realpos +
		((info->fractal->reallim[1] - realpos) * 0.95);
	info->fractal->imlim[0] = impos -
		((impos - info->fractal->imlim[0]) * 0.95);
	info->fractal->imlim[1] = impos +
		((info->fractal->imlim[1] - impos) * 0.95);
	printf("reallim = %f, %f\nimlim = %f, %f\n", info->fractal->reallim[0], info->fractal->reallim[1], info->fractal->imlim[0], info->fractal->imlim[1]);
	draw_fractal(info);
}

void		scroll_up(int x, int y, t_info *info)
{
	double		realpos;
	double		impos;

	realpos = info->fractal->reallim[0] + (x * (info->fractal->reallim[1]
				- info->fractal->reallim[0]) / WINWIDTH);
	impos = info->fractal->imlim[0] + (y * (info->fractal->imlim[1]
				- info->fractal->imlim[0]) / WINHEIGHT);
	info->fractal->reallim[0] = realpos -
		((realpos - info->fractal->reallim[0]) * 1.05);
	info->fractal->reallim[1] = realpos +
		((info->fractal->reallim[1] - realpos) * 1.05);
	info->fractal->imlim[0] = impos -
		((impos - info->fractal->imlim[0]) * 1.05);
	info->fractal->imlim[1] = impos +
		((info->fractal->imlim[1] - impos) * 1.05);
	draw_fractal(info);
}
