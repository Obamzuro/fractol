#pragma OPENCL EXTENSION cl_intel_printf : enable
#define WINWIDTH 1500
#define WINHEIGHT 1500

void	drawSierpinski(__global const double *input, __global unsigned char *output)
{
	double	x;
	double	y;
	int		depth;
	int		i;
	int		isblack;
	double	edge;
	int		xfactor;
	int		yfactor;
	int		iGid;
	int		pos;

	iGid = get_global_id(0);
	if (iGid < 0 || iGid > WINWIDTH * WINHEIGHT)
		return ;
	x = input[0] + ((iGid % WINWIDTH) * (input[1] - input[0]) / WINWIDTH);
	y = input[2] + ((iGid / WINWIDTH) * (input[3] - input[2]) / WINHEIGHT);
	depth = input[4] / 10;
	i = -1;
	edge = WINWIDTH / 3;
	isblack = 0;
	while (++i < depth && x > 0 && x < WINWIDTH && y > 0 && y < WINHEIGHT)
	{
		xfactor = x / edge;
		yfactor = y / edge;
		if (xfactor == 1 && yfactor == 1)
		{
			isblack = 1;
			break ;
		}
		x -= edge * xfactor;
		y -= edge * yfactor;
		edge /= 3;
	}
	pos = iGid * 4;
	if (isblack)
	{
		output[pos] = 0;
		output[pos + 1] = 0;
		output[pos + 2] = 0;
		output[pos + 3] = 0;
	}
	else
	{
		output[pos] = 255;
		output[pos + 1] = 255;
		output[pos + 2] = 255;
		output[pos + 3] = 0;
	}
}

__kernel void drawFractal(__global const double *input, __global unsigned char *output)
{
	int		iGid;
	double	x;
	double	y;
	double	real;
	double	realsquared;
	double	im;
	double	imsquared;
	double	nextreal;
	double	nextim;
	int		depth;
	double	color;
	int		pos;

	if (input[5] == 2)
	{
		drawSierpinski(input, output);
		return ;
	}
	iGid = get_global_id(0);
	if (iGid < 0 || iGid > WINWIDTH * WINHEIGHT)
		return ;
	x = input[0] + ((iGid % WINWIDTH) * (input[1] - input[0]) / WINWIDTH);
	y = input[2] + ((iGid / WINWIDTH) * (input[3] - input[2]) / WINHEIGHT);
	real = x;
	im = y;
	if (input[5] == 1)
	{
		x = input[6];
		y = input[7];
	}
	depth = -1;
	while (++depth < input[4])
	{
		realsquared = real * real;
		imsquared = im * im;
		if (fabs(realsquared + imsquared) > 4)
			break ;
		nextreal = realsquared - imsquared;
		nextim = 2 * real * im;
		real = nextreal + x;
		im = nextim + y;
	}
	if (depth == input[4])
		depth = 0;
	pos = iGid * 4;
	color = depth / input[4] * 255;
	if (input[8] == 0)
	{
		output[pos] = color;
		output[pos + 1] = color;
		output[pos + 2] = color;
		output[pos + 3] = 0;
	}
	else if (input[8] == 1)
	{
		output[pos] = color;
		output[pos + 1] = 0;
		output[pos + 2] = 0;
		output[pos + 3] = 0;
	}
	else if (input[8] == 2)
	{
		output[pos] = 0;
		output[pos + 1] = color;
		output[pos + 2] = 0;
		output[pos + 3] = 0;
	}
	else if (input[8] == 3)
	{
		int	mapping[16][3] =
		{
			{ 66, 30, 15 },
			{ 25, 7, 26 },
			{ 9, 1, 47 },
			{ 4, 4, 73 },
			{ 0, 7, 100 },
			{ 12, 44, 138 },
			{ 24, 82, 177 },
			{ 57, 125, 209 },
			{ 134, 181, 229 },
			{ 211, 236, 248 },
			{ 241, 233, 191 },
			{ 248, 201, 95 },
			{ 255, 170, 0 },
			{ 204, 128, 0 },
			{ 153, 87, 0 },
			{ 106, 52, 3 },
		};
		depth = depth % 16;
		output[pos] = mapping[depth][0];
		output[pos + 1] = mapping[depth][1];
		output[pos + 2] = mapping[depth][2];
		output[pos + 3] = 0;
	}
}
