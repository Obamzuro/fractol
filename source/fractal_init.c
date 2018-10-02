/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:20:55 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 21:23:38 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		fractal_init(t_fractal *fractal)
{
	if (fractal->type == SIERPINSKI_CARPET)
	{
		fractal->reallim[0] = 0;
		fractal->reallim[1] = WINWIDTH;
		fractal->imlim[0] = 0;
		fractal->imlim[1] = WINHEIGHT;
		fractal->depth = 16;
	}
	else
	{
		fractal->reallim[0] = -2;
		fractal->reallim[1] = 2;
		fractal->imlim[0] = -2;
		fractal->imlim[1] = 2;
		fractal->depth = 100;
	}
	fractal->ismousesensitive = 1;
	return (0);
}
