#include "../minirt.h"

float	plane(t_3d_point p, t_3d_point n, float h)
{
	return (dot(p, n) + h);
}

t_plan	*init_plan(t_shapes *shapes)
{
	int		i;
	t_plan	*plan;

	plan = malloc(sizeof(t_plan) * shapes->nmb_plane);
	i = 0;
	while (i < shapes->nmb_plane)
	{
		plan[i].z = 1;
		plan[i].light.direction = vecteur_normalise(shapes->light.orig);
		plan[i].light.lumnosite = shapes->light.light_bright;
		plan[i].centre_screen_x = HEIGHT / 2.f;
		plan[i].centre_screen_y = WIDTH / 2.f;
		plan[i].position = shapes->plane[i].point;
		plan[i].normal = shapes->plane[i].norm_vect;
		plan[i].color.r = shapes->plane[i].color.x;
		plan[i].color.g = shapes->plane[i].color.z;
		plan[i].color.b = shapes->plane[i].color.y;
		i++;
	}
	return (plan);
}


