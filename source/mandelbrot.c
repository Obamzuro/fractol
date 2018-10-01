/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 18:52:58 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/01 22:53:05 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//static int	calc_depth(t_info *info, double x, double y)
//{
//	double		real;
//	double		im;
//	double		nextreal;
//	double		nextim;
//	int			i;
//
//	x = info->fractal->reallim[0] + (x * (info->fractal->reallim[1]
//				- info->fractal->reallim[0]) / WINWIDTH);
//	y = info->fractal->imlim[0] + (y * (info->fractal->imlim[1]
//				- info->fractal->imlim[0]) / WINHEIGHT);
//	real = x;
//	im = y;
//	i = -1;
//	while (++i < info->fractal->depth)
//	{
//		if (fabs(real * real + im * im) > 4)
//			return (i);
//		nextreal = real * real - im * im;
//		nextim = 2 * real * im;
//		real = nextreal + x;
//		im = nextim + y;
////		if (fabs(real + im) > 16)
////			return (i);
//	}
//	return (i);
//}
//
//void		draw_mandelbrot(t_info *info)
//{
//	double	x;
//	double	y;
//	int		n;
//
//	x = -1;
//	while (++x < WINWIDTH)
//	{
//		y = -1;
//		while (++y < WINHEIGHT)
//		{
////			if (y == WINHEIGHT / 2 || x == WINWIDTH / 2)
////			{
////				*(info->img + (int)(y * info->size_line + x * 4) + 0) = 0;
////				*(info->img + (int)(y * info->size_line + x * 4) + 1) = 0;
////				*(info->img + (int)(y * info->size_line + x * 4) + 2) = 255;
////				*(info->img + (int)(y * info->size_line + x * 4) + 3) = 0;
////			continue ;
////			}
//			n = calc_depth(info, x, y);
//			if (n == info->fractal->depth)
//				n = 0;
//			else
//				n = n / (double)info->fractal->depth * 255;
//			*(info->img + (int)(y * info->size_line + x * 4) + 0) = n;
//			*(info->img + (int)(y * info->size_line + x * 4) + 1) = n;
//			*(info->img + (int)(y * info->size_line + x * 4) + 2) = n;
//			*(info->img + (int)(y * info->size_line + x * 4) + 3) = 0;
//		}
//	}
//}

int			draw_fractal(t_info *info)
{
	double		input[6];
	cl_mem		inbuffer;
	cl_mem		outbuffer;
	cl_int		status;
	t_clinfo	*cl;

	cl = info->cl;
	input[0] = info->fractal->reallim[0];
	input[1] = info->fractal->reallim[1];
	input[2] = info->fractal->imlim[0];
	input[3] = info->fractal->imlim[1];
	input[4] = info->fractal->depth;
	input[5] = info->fractal->type;
	inbuffer = clCreateBuffer(info->cl->context, CL_MEM_READ_ONLY |
			CL_MEM_COPY_HOST_PTR, sizeof(input), input, &status);
	if (status != CL_SUCCESS && write(2, "Error: inBufferCreating\n", 24))
		return (-1);
	outbuffer = clCreateBuffer(info->cl->context, CL_MEM_READ_WRITE |
			CL_MEM_COPY_HOST_PTR, WINHEIGHT * WINWIDTH * 4, info->img, &status);
	if (status != CL_SUCCESS && write(2, "Error: outBufferCreating\n", 25))
		return (-1);
	clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &inbuffer);
	clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &outbuffer);
	if (clEnqueueWriteBuffer(cl->queue, inbuffer, CL_FALSE, 0,
			sizeof(input), input, 0, NULL, NULL) != CL_SUCCESS)
	{
		write(2, "Error: writeBuffer\n", 19);
		return (-1);
	}
	size_t		global_work_size;
	global_work_size = WINHEIGHT * WINWIDTH;
	if (clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL,
				&global_work_size, NULL, 0, NULL, NULL) != CL_SUCCESS)
	{
		write(2, "Error: clEnqueueNDRangeKernel\n", 30);
		return (-1);
	}
	if (clEnqueueReadBuffer(cl->queue, outbuffer, CL_TRUE, 0,
				4 * WINHEIGHT * WINWIDTH, info->img, 0, NULL, NULL) != CL_SUCCESS)
	{
		write(2, "Error: clEnqueueReadBuffer\n", 27);
		return (-1);
	}
	mlx_put_image_to_window(info->mlx, info->win,
			info->img_ptr, 0, 0);
	return (0);
}
