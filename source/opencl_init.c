/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:58:56 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 20:39:03 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"




static int		build_program(t_clinfo *cl)
{
	cl_int		status;
	char		*source;

	if (!(source = load_kernel(KERNEL_SRC)))
		return (-1);
	if (!(cl->program = create_program(source, cl->context)))
		return (-1);
	status = clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL);
if (status == CL_BUILD_PROGRAM_FAILURE)
{
   // Determine the size of the log
       size_t log_size;
       clGetProgramBuildInfo(cl->program, cl->device,
       CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

   // Allocate memory for the log
       char *log = (char* ) malloc(log_size);

   // Get the log
       clGetProgramBuildInfo(cl->program, cl->device,
       CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

   // Print the log
       printf("%s\n", log);
}
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init Build program.\n");
		return (-1);
	}
	return (0);
}

static int		create_kernel_queue(t_clinfo *cl)
{
	cl_int		status;

	cl->kernel = clCreateKernel(cl->program, "drawFractal", &status);
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init create Kernel.\n");
		return (-1);
	}
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, &status);
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init create Qeueue.\n");
		return (-1);
	}
	return (0);
}

/*
** Norminette WTF?
** doesn't work with sizeof(double) in args of func
*/

static int		create_buffers(t_clinfo *cl)
{
	cl_int		status;
	size_t		shit;

	shit = AM_INPUT_ARGS_CL * sizeof(double);
	cl->inbuffer = clCreateBuffer(cl->context, CL_MEM_READ_ONLY,
			shit, NULL, &status);
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init inBufferCreating\n");
		return (-1);
	}
	cl->outbuffer = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			WINSQUARE * 4, NULL, &status);
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init outBufferCreating\n");
		return (-1);
	}
	return (0);
}

int				opencl_init(t_clinfo *cl)
{
	if (!(cl->platform = get_platform()))
		return (-1);
	if (!(cl->device = get_device(cl)))
		return (-1);
	if (!(cl->context = get_context(cl)))
		return (-1);
	if (build_program(cl))
		return (-1);
	if (create_kernel_queue(cl))
		return (-1);
	if (create_buffers(cl))
		return (-1);
	clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->inbuffer);
	clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->outbuffer);
	return (0);
}

void			opencl_release(t_clinfo *cl)
{
	clReleaseCommandQueue(cl->queue);
	clReleaseMemObject(cl->inbuffer);
	clReleaseMemObject(cl->outbuffer);
	clReleaseKernel(cl->kernel);
	clReleaseProgram(cl->program);
	clReleaseContext(cl->context);
}
