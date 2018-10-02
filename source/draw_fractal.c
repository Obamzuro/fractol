/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:34:38 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 19:45:04 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fill_input(t_info *info, double input[AM_INPUT_ARGS_CL])
{
	input[0] = info->fractal->reallim[0];
	input[1] = info->fractal->reallim[1];
	input[2] = info->fractal->imlim[0];
	input[3] = info->fractal->imlim[1];
	input[4] = info->fractal->depth;
	input[5] = info->fractal->type;
	if (info->fractal->type == JULIA)
	{
		input[6] = info->fractal->constant[0];
		input[7] = info->fractal->constant[1];
	}
	input[8] = info->fractal->colormode;
}

static int	opencl_executing(t_info *info, double input[AM_INPUT_ARGS_CL])
{
	size_t		global_work_size;
	t_clinfo	*cl;

	cl = info->clinfo;
	global_work_size = WINSQUARE;
	if (clEnqueueWriteBuffer(cl->queue, cl->inbuffer, CL_FALSE, 0,
			AM_INPUT_ARGS_CL * sizeof(double), input,
			0, NULL, NULL) != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_exec writeBuffer\n");
		return (-1);
	}
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL,
				&global_work_size, NULL, 0, NULL, NULL) != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_exec clEnqueueNDRangeKernel\n");
		return (-1);
	}
	if (clEnqueueReadBuffer(cl->queue, cl->outbuffer, CL_TRUE, 0,
				4 * WINSQUARE, info->mlxinfo->img, 0, NULL, NULL) != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_exec clEnqueueReadBuffer\n");
		return (-1);
	}
	return (0);
}

int			draw_fractal(t_info *info)
{
	double		input[AM_INPUT_ARGS_CL];

	fill_input(info, input);
	opencl_executing(info, input);
	mlx_put_image_to_window(info->mlxinfo->mlx, info->mlxinfo->win,
			info->mlxinfo->img_ptr, 0, 0);
	return (0);
}
