/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_color_changers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 19:11:02 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 15:32:34 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		is_setcolor_keycode(int keycode)
{
	if ((keycode >= 6 && keycode <= 9) || keycode == 11)
		return (1);
	return (0);
}

int				set_color(t_info *info, int keycode)
{
	if (!is_setcolor_keycode(keycode) ||
			info->fractal->type == SIERPINSKI_CARPET)
		return (0);
	if (keycode == 6)
		info->fractal->colormode = NORMAL;
	else if (keycode == 7)
		info->fractal->colormode = BLUE;
	else if (keycode == 8)
		info->fractal->colormode = GREEN;
	else if (keycode == 9)
		info->fractal->colormode = RED;
	else if (keycode == 11)
		info->fractal->colormode = PSYCHO;
	draw_fractal(info);
	return (1);
}
