/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:12:52 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 20:03:31 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		increase_depth(t_info *info)
{
	info->fractal->depth += 10;
	draw_fractal(info);
}

void		decrease_depth(t_info *info)
{
	if (info->fractal->depth > 20)
	{
		info->fractal->depth -= 10;
		draw_fractal(info);
	}
}
