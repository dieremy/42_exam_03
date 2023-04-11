#include "micro_paint.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_perror(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

int	check_pos(float x, float y, float centre_x, float centre_y, float width, float height)
{
	if (x < centre_x || x > centre_x + width || y < centre_y || y > centre_y + height)
		return (0);
	else if (x - centre_x < 1.0000000 || (centre_x + width) - x < 1.0000000 ||
			y - centre_y < 1.0000000 || (centre_y + height) - y < 1.0000000)
		return (1);
	return (2);
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

	if (ac != 2)
		return (ft_perror(ERR1));
	if (!(f = fopen(av[1], "r")) ||
		(fscanf(f, "%d %d %c\n", &b_width, &b_height, &background) != 3) ||
		(!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300)) ||
		(!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))
		return (ft_perror(ERR2));
	memset(canvas, background, b_width * b_height);
	while ((read = fscanf(f, "%c %f %f %f %f %c\n", &id, &centre_x, &centre_y, &width, &height, &color)) == 6)
	{
		if (!(width > 0 && height > 0) || !(id == 'R' || id == 'r'))
			break;
		y = -1;
		while (++y < b_height)
		{
			x = -1;
			while (++x < b_width)
			{
				pos = check_pos((float)x, (float)y, centre_x, centre_y, width, height);
				if (pos == 1 || (pos == 2 && id == 'R'))
					canvas[y * b_width + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(canvas);
		return (ft_perror(ERR2));
	}
	y = -1;
	while (++y < b_height)
	{
		write(1, canvas + y  * b_width, b_width);
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(f);
	return (0);
}
