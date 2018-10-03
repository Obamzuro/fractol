/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:07:30 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/03 16:06:30 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_mlx_init(t_mlxinfo *mlxinfo)
{
	if (!(mlxinfo->mlx = mlx_init()))
	{
		ft_fprintf(STDERR_FILENO, "fractol: Error: mlx_init()");
		return (-1);
	}
	if (!(mlxinfo->win = mlx_new_window(mlxinfo->mlx,
				WINWIDTH, WINHEIGHT, "FRACTOL")))
	{
		ft_fprintf(STDERR_FILENO, "fractol: Error: mlx_new_window()");
		return (-1);
	}
	if (!(mlxinfo->img_ptr = mlx_new_image(mlxinfo->mlx,
				WINWIDTH, WINHEIGHT)))
	{
		ft_fprintf(STDERR_FILENO, "fractol: Error: mlx_new_image()");
		return (-1);
	}
	if (!(mlxinfo->img = (unsigned char *)mlx_get_data_addr(mlxinfo->img_ptr,
			&mlxinfo->bits_per_pixel, &mlxinfo->size_line, &mlxinfo->endian)))
	{
		ft_fprintf(STDERR_FILENO, "fractol: Error: mlx_get_data_addr()");
		return (-1);
	}
	return (0);
}
