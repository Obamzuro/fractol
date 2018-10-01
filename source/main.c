/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/01 23:06:46 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			set_intensity_on(int red, int green, int blue, double change)
{
	int		result;

	result = (int)(red) << 16;
	result |= (int)(green) << 8;
	result |= (int)(blue);
	result |= (int)((1 - change) * 255) << 24;
	return (result);
}

static int	ft_exit(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	exit(EXIT_SUCCESS);
}

static int	key_press(int keycode, void *param)
{
	printf("%d", 1);
	if (keycode == 49)
		ft_exit(keycode, param);
	else if (keycode == 53)
		ft_exit(keycode, param);
	(void)keycode;
	return (0);
}

void		scroll_down(int x, int y, t_info *info)
{
	double		realpos;
	double		impos;

	realpos = info->fractal->reallim[0] + (x * (info->fractal->reallim[1]
				- info->fractal->reallim[0]) / WINWIDTH);
	impos = info->fractal->imlim[0] + (y * (info->fractal->imlim[1]
				- info->fractal->imlim[0]) / WINHEIGHT);
	info->fractal->reallim[0] = realpos - ((realpos - info->fractal->reallim[0]) * 0.95);
	info->fractal->reallim[1] = realpos + ((info->fractal->reallim[1] - realpos) * 0.95);
	info->fractal->imlim[0] = impos - ((impos - info->fractal->imlim[0]) * 0.95);
	info->fractal->imlim[1] = impos + ((info->fractal->imlim[1] - impos) * 0.95);
	draw_fractal(info);
}

static int	mouse_press(int button, int x, int y, void *param)
{
	t_info		*info;

	info = (t_info *)param;
	(void)x;
	(void)y;
	(void)button;
	printf("%d", 1);
	if (button == 5)
		scroll_down(x, y, info);
	return (0);
}

int			main(int argc, char **argv)
{
	t_info		info;
	t_fractal	fractal;
	int			temp;
	int			temp2;

	(void)argc;
	(void)argv;
//	if (!argv[1])
//	{
//		write(1, "Usage: ./fractol [Mandelbrot]\n", 30);
//		return (0);
//	}
	ft_bzero(&info, sizeof(t_info));
	info.mlx = mlx_init();
	info.win = mlx_new_window(info.mlx, WINWIDTH, WINHEIGHT, "FRACTOL");
	info.img_ptr = mlx_new_image(info.mlx, WINWIDTH, WINHEIGHT);
	info.img = (unsigned char *)mlx_get_data_addr(info.img_ptr, &temp, &info.size_line, &temp2);
	info.fractal = &fractal;
	fractal.reallim[0] = -2;
	fractal.reallim[1] = 2;
	fractal.imlim[0] = -2;
	fractal.imlim[1] = 2;
	fractal.depth = 20;
	fractal.type = MANDELBROT;
	printf("bitsper = %d\nsize_line = %d\nendian = %d\n", temp, info.size_line, temp2);
	info.cl = (t_clinfo *)ft_memalloc(sizeof(t_clinfo));
	if (opencl_init(info.cl) == -1)
		return (-1);
	draw_fractal(&info);
	mlx_hook(info.win, 2, 5, key_press, &info);
	mlx_hook(info.win, 17, 1L << 17, ft_exit, &info);
	mlx_hook(info.win, 4, 5, mouse_press, &info);
	mlx_loop(info.mlx);
	return (0);
}
