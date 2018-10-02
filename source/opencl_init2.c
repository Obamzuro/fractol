/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:32:46 by obamzuro          #+#    #+#             */
/*   Updated: 2018/10/02 16:46:13 by obamzuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

char			*load_kernel(const char *name)
{
	int		fd;
	char	line[BUFFER_SIZE_CL + 1];
	char	*temp;
	char	*ret;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init Open Kernel file");
		return (NULL);
	}
	ret = NULL;
	ft_bzero(line, sizeof(line));
	while (read(fd, &line, BUFFER_SIZE_CL) > 0)
	{
		temp = ret;
		ret = ft_strjoin(ret, line);
		free(temp);
		ft_bzero(line, sizeof(line));
	}
	close(fd);
	return (ret);
}

cl_program		create_program(char *source, cl_context context)
{
	const char	*sources[1] = { source };
	cl_int		error;
	cl_program	program;

	program = clCreateProgramWithSource(context, 1, sources, NULL, &error);
	if (error != CL_SUCCESS)
	{
		ft_fprintf(2, "Error: cl_init CreateProgramWS %d\n", error);
		return (NULL);
	}
	free(source);
	return (program);
}

cl_platform_id	get_platform(void)
{
	cl_uint					num_platforms;
	cl_platform_id			*platforms;
	cl_platform_id			platform;
	cl_int					status;

	platform = NULL;
	status = clGetPlatformIDs(0, NULL, &num_platforms);
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init Getting Platforms.\n");
		return (NULL);
	}
	if (num_platforms > 0)
	{
		platforms = malloc(num_platforms * sizeof(cl_platform_id));
		status = clGetPlatformIDs(num_platforms, platforms, NULL);
		if (status != CL_SUCCESS)
		{
			ft_fprintf(STDERR_FILENO, "Error: cl_init Getting Platform IDs.\n");
			return (NULL);
		}
		platform = platforms[0];
		free(platforms);
	}
	return (platform);
}

cl_device_id	get_device(t_clinfo *cl)
{
	cl_device_id			*devices;
	cl_device_id			device;
	cl_uint					num_devices;

	device = NULL;
	if (clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU,
			0, NULL, &num_devices) != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init Getting Devices.\n");
		return (NULL);
	}
	if (num_devices > 0)
	{
		devices = malloc(num_devices * sizeof(cl_device_id));
		if (clGetDeviceIDs(cl->platform, CL_DEVICE_TYPE_GPU,
					1, devices, NULL) != CL_SUCCESS)
		{
			ft_fprintf(STDERR_FILENO, "Error: cl_init Getting Device Ids.\n");
			return (NULL);
		}
		device = devices[0];
		free(devices);
	}
	return (device);
}

cl_context		get_context(t_clinfo *cl)
{
	cl_context					context;
	cl_int						status;
	const cl_context_properties	context_properties[] =
	{ CL_CONTEXT_PLATFORM, (cl_context_properties)cl->platform, 0, 0 };

	context = clCreateContext(context_properties,
			1, &cl->device, 0, 0, &status);
	if (status != CL_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "Error: cl_init Create context.\n");
		return (NULL);
	}
	return (context);
}
