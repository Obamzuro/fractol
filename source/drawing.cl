#pragma OPENCL EXTENSION cl_intel_printf : enable
#define WINWIDTH 1500
#define WINHEIGHT 1500

__kernel void drawFractal(__global const double *input, __global unsigned char *output)
{
	int		iGid;
	double	x;
	double	y;
	double	real;
	double	im;
	double	nextreal;
	double	nextim;
	int		i;

	iGid = get_global_id(0);
	if (iGid < 0 || iGid > WINWIDTH * WINHEIGHT)
		return ;
	x = input[0] + ((iGid % WINWIDTH) * (input[1] - input[0]) / WINWIDTH);
	y = input[2] + ((iGid / WINWIDTH) * (input[3] - input[2]) / WINHEIGHT);
	real = x;
	im = y;
	i = -1;
	while (++i < input[4])
	{
		if (fabs(real * real + im * im) > 4)
			break ;
		nextreal = real * real - im * im;
		nextim = 2 * real * im;
		real = nextreal + x;
		im = nextim + y;
	}
	if (i == input[4])
		i = 0;
	output[iGid * 4] = i / input[4] * 255;
	output[iGid * 4 + 1] = i / input[4] * 255;
	output[iGid * 4 + 2] = i / input[4] * 255;
	output[iGid * 4 + 3] = 0;
}
