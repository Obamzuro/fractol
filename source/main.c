/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 14:12:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 16:02:26 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_exit(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	exit(EXIT_SUCCESS);
}

static int	key_press(int keycode, void *param)
{
	t_info		*info;

	info = (t_info *)param;
	if (keycode == 53)
		ft_exit(keycode, param);
	else if (keycode == 49)
		info->fractal->ismousesensitive = !info->fractal->ismousesensitive;
	else if (change_direction(info, keycode))
		;
	else if (change_depth(info, keycode))
		;
	else if (set_fractal(info, keycode))
		;
	else if (set_color(info, keycode))
		;
	return (0);
}

static int	mouse_press(int button, int x, int y, void *param)
{
	t_info		*info;

	info = (t_info *)param;
	if (button == 5)
		scroll_down(x, y, info);
	else if (button == 4)
		scroll_up(x, y, info);
	return (0);
}

static int	mouse_move(int x, int y, void *param)
{
	t_info		*info;

	info = (t_info *)param;
	if (info->fractal->type != JULIA || !info->fractal->ismousesensitive)
		return (0);
	info->fractal->constant[0] = -1 + (2.0 * x / WINWIDTH);
	info->fractal->constant[1] = -1 + (2.0 * y / WINHEIGHT);
	draw_fractal(info);
	return (0);
}

int			main(int argc, char **argv)
{
	t_info		info;

	(void)argc;
	ft_bzero(&info, sizeof(t_info));
	info.fractal = (t_fractal *)ft_memalloc(sizeof(t_fractal));
	handle_parameter(info.fractal, argv);
	if (fractal_init(info.fractal))
		return (-1);
	info.mlxinfo = (t_mlxinfo *)ft_memalloc(sizeof(t_mlxinfo));
	if (ft_mlx_init(info.mlxinfo))
		return (-1);
	info.clinfo = (t_clinfo *)ft_memalloc(sizeof(t_clinfo));
	if (opencl_init(info.clinfo))
		return (-1);
	draw_fractal(&info);
	mlx_hook(info.mlxinfo->win, 2, 5, key_press, &info);
	mlx_hook(info.mlxinfo->win, 17, 1L << 17, ft_exit, &info);
	mlx_hook(info.mlxinfo->win, 4, 5, mouse_press, &info);
	mlx_hook(info.mlxinfo->win, 6, 5, mouse_move, &info);
	mlx_loop(info.mlxinfo->mlx);
	opencl_release(info.clinfo);
	return (0);
}
