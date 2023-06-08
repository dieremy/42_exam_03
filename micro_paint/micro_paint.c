#include "micro_paint.h"

int	ft_perror(char *s)
{
	// when called, function termination 
	// ERR1 or ERR2 declared in micro_paint.h
	while (*s)
		write(1, s++, 1);
	return (1);
}

int	check_pos(float x, float y, float centre_x, float centre_y, float width, float height)
{
	if (x < centre_x || x > centre_x + width || y < centre_y || y > centre_y + height)
		return (0);	// check outside square
	else if (x - centre_x < 1.0000000 || (centre_x + width) - x < 1.0000000 ||
			y - centre_y < 1.0000000 || (centre_y + height) - y < 1.0000000)
		return (1);	// check border
	return (2);		// check inside square
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
	float	centre_x, centre_y, width, height;

	if (ac != 2)		// check on wrong number of parameters
		return (ft_perror(ERR1));
	if (!(f = fopen(av[1], "r")) ||													// argv[1]-file cannot be opened
		(fscanf(f, "%d %d %c\n", &b_width, &b_height, &background) != 3) ||			// first line of file has not right parameters
		(!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300)) ||	// background has not right dimension
		(!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height))))) 			// cannot allocate right amount of memory
		return (ft_perror(ERR2));
	memset(canvas, background, b_width * b_height);									// background drawing
	while ((read = fscanf(f, "%c %f %f %f %f %c\n", &id, &centre_x, &centre_y, &width, &height, &color)) == 6) // repeat if the condition is met
	{
		if (!(width > 0 && height > 0) || !(id == 'R' || id == 'r'))				// if size is negative or id is not 'r' / 'R'
			break;
		y = -1;
		while (++y < b_height)
		{
			x = -1;
			while (++x < b_width)
			{
				pos = check_pos((float)x, (float)y, centre_x, centre_y, width, height);	// check area
				if (pos == 1 || (pos == 2 && id == 'R'))
					canvas[y * b_width + x] = color;									// drawing
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
		write(1, canvas + y  * b_width, b_width);	// painting
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(f);
	return (0);
}
