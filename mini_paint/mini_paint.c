#include "mini_paint.h"

int	ft_perror(char *s)
{
	// when called, function termination 
	// ERR1 or ERR2 declared in mini_paint.h
	while(*s)
		write(1, s++, 1);
	return (1);
}

int	check_pos(float x, float y, float centre_x, float centre_y, float radius)
{
	float distance = sqrtf(powf(x - centre_x, 2.) + powf(y - centre_y, 2.));
	if (distance <= radius)
	{
		if ((radius - distance) < 1.0000000)
			return (0); // check border circle
		return (1);		// check inside circle
	}
	return (2);			// check outside circle
}

int main(int ac, char *av[])
{
	FILE	*f;
	char	*canvas;
	int		read, pos;
	int		x, y;

	int		b_width, b_height;
	char	background;

	char	id, color;
	float	centre_x, centre_y, radius;
	
	if (ac != 2)		// check on wrong number of parameters
		return (ft_perror(ERR1));
	if (!(f = fopen(av[1], "r"))													// argv[1]-file cannot be opened
		|| (fscanf(f, "%d %d %c\n", &b_width, &b_height, &background) != 3)			// first line of file has not right parameters	
		|| (!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300))	// background has not right dimension
		|| (!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))		// cannot allocate right amount of memory
		return (ft_perror(ERR2));
	memset(canvas, background, b_width * b_height);									// background drawing
	while ((read = fscanf(f, "%c %f %f %f %c\n", &id, &centre_x, &centre_y, &radius, &color)) == 5)		// repeat if the condition is met
	{
		if (!(radius > 0) || !(id == 'C' || id == 'c'))								// if size is negative or id is not 'c' / 'C'
			break;
		y = -1;
		while (++y < b_height)
		{
			x = -1;
			while (++x < b_width)
			{
				pos = check_pos((float)x, (float)y, centre_x, centre_y, radius);	// check area
				if (pos == 0 || (pos == 1 && id == 'C'))
					canvas[y * b_width + x] = color;								// drawing
			}
		}
	}
	if (read != -1)			// previous reading escaped so badly the loop
	{
		free(canvas);
		return (ft_perror(ERR2));
	}
	y = -1;
	while (++y < b_height)
	{
		write(1, canvas + y * b_width, b_width);	// painting
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(f);
	return (0);
}
