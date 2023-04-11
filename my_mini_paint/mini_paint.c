#include "mini_paint.h"

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_perror(char *s)
{
	write(1, s, ft_strlen(s));
	return (1);
}

int	check_pos(float x, float y, float centre_x, float centre_y, float radius)
{
	float distance = sqrtf(powf(x - centre_x, 2.) + powf(y - centre_y, 2.));
	if (distance <= radius)
	{
		if ((radius - distance) < 1.0000000)
			return (0);
		return (1);
	}
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
	float	centre_x, centre_y, radius;
	
	if (ac != 2)
		return (ft_perror(ERR1));
	if (!(f = fopen(av[1], "r"))
		|| (fscanf(f, "%d %d %c\n", &b_width, &b_height, &background) != 3)
		|| (!(b_width > 0 && b_width <= 300 && b_height > 0 && b_height <= 300))
		|| (!(canvas = (char *)malloc(sizeof(char) * (b_width * b_height)))))
		return (ft_perror(ERR2));
	memset(canvas, background, b_width * b_height);
	while ((read = fscanf(f, "%c %f %f %f %c\n", &id, &centre_x, &centre_y, &radius, &color)) == 5)
	{
		if (!(radius > 0) || !(id == 'C' || id == 'c'))
			break;
		y = -1;
		while (++y < b_height)
		{
			x = -1;
			while (++x < b_width)
			{
				pos = check_pos((float)x, (float)y, centre_x, centre_y, radius);
				if (pos == 0 || (pos == 1 && id == 'C'))
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
		write(1, canvas + y * b_width, b_width);
		write(1, "\n", 1);
	}
	free(canvas);
	fclose(f);
	return (0);
}
