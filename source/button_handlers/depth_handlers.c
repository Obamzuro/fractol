/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:12:52 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 15:30:26 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		increase_depth(t_info *info)
{
	info->fractal->depth += 10;
	draw_fractal(info);
}

static void		decrease_depth(t_info *info)
{
	if (info->fractal->depth > 20)
	{
		info->fractal->depth -= 10;
		draw_fractal(info);
	}
}

int				change_depth(t_info *info, int keycode)
{
	if (keycode == 69)
	{
		increase_depth(info);
		return (1);
	}
	else if (keycode == 78)
	{
		decrease_depth(info);
		return (1);
	}
	return (0);
}
