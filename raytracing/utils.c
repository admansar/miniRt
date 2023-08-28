#include "../minirt.h"

t_3d_point	color_multi(t_3d_point a, t_rgb color)
{
	return (vec3(a.x * color.r, a.y * color.b, a.z * color.g));
}

int	min_tab_index(float *tab, int size)
{
	int		i;
	int		min_index;
	float	min;

	min = tab[0];
	i = 0;
	min_index = 0;
	while (i < size)
	{
		if (min > tab[i])
		{
			min = tab[i];
			min_index = i;
		}
		i++;
	}
	return (min_index);
}

void	stay_a_color(int *color)
{
	if ((*color) > 255)
		(*color) = 255;
	else if ((*color) < 0)
		(*color) = 0;
}

int	rgb_to_int(int r, int g, int b)
{
	int	color;

	stay_a_color(&r);
	stay_a_color(&g);
	stay_a_color(&b);
	color = (r << 16) | (g << 8) | b;
	return (color);
}


