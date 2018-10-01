#define WINWIDTH 1500
#define WINHEIGHT 1500

__kernel void drawFractal(__global const double *input, __global char *output)
{
	int		iGid;
	double	x;
	double	y;
	int		i;

	iGid = get_global_id(0);
	if (iGid < 0 || iGid > WINWIDTH * WINHEIGHT)
		return ;
	x = input[0] + ((iGid % WINWIDTH) * (input[1] - input[0]) / WINWIDTH);
	y = input[2] + ((iGid / WINWIDTH) * (input[3] - input[2]) / WINHEIGHT);
	if (readl * real + im * im < 4)
	{
		output[y * WINWIDTH + x] = 255;
		output[y * WINWIDTH + x + 1] = 255;
		output[y * WINWIDTH + x + 2] = 255;
		output[y * WINWIDTH + x + 3] = 0;
	}
	else
	{
		output[y * WINWIDTH + x] = 0;
		output[y * WINWIDTH + x + 1] = 0;
		output[y * WINWIDTH + x + 2] = 0;
		output[y * WINWIDTH + x + 3] = 0;
	}
}
