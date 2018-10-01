/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 19:58:56 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/01 22:44:04 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char	*LoadKernel(const char *name)
{
	int		fd;
	char	line[1001];
	char	*temp;
	char	*ret;

	fd = open(name, O_RDONLY);
	ret = NULL;
	ft_bzero(line, sizeof(line));
	while (read(fd, &line, 1000) > 0)
	{
		temp = ret;
		ret = ft_strjoin(ret, line);
		free(temp);
		ft_bzero(line, sizeof(line));
	}
	close(fd);
	return (ret);
}

cl_program	CreateProgram(char *source, cl_context context)
{
	const char	*sources[1] = { source };
	cl_int	error = 0;

	cl_program program = clCreateProgramWithSource(context, 1, sources, NULL, &error);
	if (error != CL_SUCCESS)
	{
		ft_printf("Error: CreateProgramWS %d\n", error);
		return (NULL);
	}
	free(source);
	return (program);
}

cl_platform_id	getPlatform(void)
{
	cl_uint					numPlatforms;
	cl_platform_id			*platforms;
	cl_platform_id			platform;
	cl_int					status;

	platform = NULL;
	status = clGetPlatformIDs(0, NULL, &numPlatforms);
	if (status != CL_SUCCESS)
	{
		write(2, "Error: Getting Platforms.\n", 26);
		return (NULL);
	}
	if (numPlatforms > 0)
	{
		platforms = (cl_platform_id *)malloc(numPlatforms * sizeof(cl_platform_id));
		status = clGetPlatformIDs(numPlatforms, platforms, NULL);
		if (status != CL_SUCCESS)
		{
			write(2, "Error: Getting Platform Ids.\n", 29);
			return (NULL);
		}
		platform = platforms[0];
		free(platforms);
	}
	return (platform);
}

cl_device_id	getDevice(t_clinfo *cl)
{
	cl_device_id			*devices;
	cl_device_id			device;
	cl_int					status;
	cl_uint					numDevices;

	status = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
	device = NULL;
	if (status != CL_SUCCESS)
	{
		write(2, "Error: Getting devices.\n", 26);
		return (NULL);
	}
	if (numDevices > 0)
	{
		devices = (cl_device_id *)malloc(numDevices * sizeof(cl_device_id));
		status = clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU, 1, devices, NULL);
		if (status != CL_SUCCESS)
		{
			write(2, "Error: Getting Device Ids.\n", 29);
			return (NULL);
		}
		device = devices[0];
		free(devices);
	}
	return (device);
}

cl_context		getContext(t_clinfo *cl)
{
	cl_context		context;
	cl_int			status;

//	const cl_context_properties contextProperties[] =
//	{CL_CONTEXT_PLATFORM, (cl_context_properties)platform, 0, 0};
	context = clCreateContext(NULL,
			1, &cl->device, 0, 0, &status);
	if (status != CL_SUCCESS)
	{
		write(2, "Error: Create context.\n", 23);
		return (NULL);
	}
	return (context);
}

int				opencl_init(t_clinfo *cl)
{
	cl_int					error;

	if (!(cl->platform = getPlatform()))
		return (-1);
	if (!(cl->device = getDevice(cl)))
		return (-1);
	if (!(cl->context = getContext(cl)))
		return (-1);
	if (!(cl->program = CreateProgram(LoadKernel("source/drawing.cl"), cl->context)))
		return (-1);
	error = clBuildProgram(cl->program, 1, &cl->device, NULL, NULL, NULL);
if (error == CL_BUILD_PROGRAM_FAILURE) 
        {
           // Determine the size of the log
               size_t log_size;
               clGetProgramBuildInfo(cl->program, cl->device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

           // Allocate memory for the log
               char *log = (char* ) malloc(log_size);

           // Get the log
               clGetProgramBuildInfo(cl->program, cl->device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

           // Print the log
               printf("%s\n", log);
        }
	if (error != CL_SUCCESS)
	{
		write(2, "Error: Build program.\n", 22);
		return (-1);
	}
	cl->kernel = clCreateKernel(cl->program, "drawFractal", &error);
	if (error != CL_SUCCESS)
	{
		write(2, "Error: create Kernel.\n", 22);
		return (-1);
	}
	cl->queue = clCreateCommandQueue(cl->context, cl->device, 0, &error);
	if (error != CL_SUCCESS)
	{
		write(2, "Error: create Qeueue.\n", 22);
		return (-1);
	}
	return (0);
}

//{
//	status = clEnqueueReadBuffer(queue, bBuffer, CL_TRUE, 0, sizeof(float) * testDataSize, b, 0, NULL, NULL);
//	if (status != CL_SUCCESS)
//	{
//		write(2, "Error: Enqueue read.\n", 21);
//		return (-1);
//	}
//
//	clReleaseCommandQueue(queue);
//
//	clReleaseMemObject(bBuffer);
//	clReleaseMemObject(aBuffer);
//
//	clReleaseKernel(kernel);
//	clReleaseProgram(program);
//
//	clReleaseContext(context);
//}
