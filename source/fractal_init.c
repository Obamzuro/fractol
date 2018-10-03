/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:20:55 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 16:25:14 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_parameter_error(void)
{
	ft_fprintf(2, "Usage: ./fractol [type]\n\
			MANDELBROT        - m,\n\
			JULIA             - j,\n\
			BUFFALO           - b,\n\
			BURNING_SHIP      - bs,\n\
			TRICORN           - t,\n\
			SIERPINSKI_CARPET - s\n");
	exit(EXIT_FAILURE);
}

t_fractal_corr		g_fractalcorr[] =
{
	{"m", MANDELBROT},
	{"j", JULIA},
	{"b", BUFFALO},
	{"bs", BURNING_SHIP},
	{"t", TRICORN},
	{"s", SIERPINSKI_CARPET}
};

void	handle_parameter(t_fractal *fractal, char **argv)
{
	size_t				i;

	if (!argv[1])
		handle_parameter_error();
	i = -1;
	while (++i < sizeof(g_fractalcorr) / sizeof(t_fractal_corr))
	{
		if (ft_strequ(argv[1], g_fractalcorr[i].shortcut))
		{
			fractal->type = g_fractalcorr[i].type;
			return ;
		}
	}
	handle_parameter_error();
}

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
