#include "../minirt.h"

float	sdcapsule(t_3d_point p, t_3d_point a, t_3d_point b, float r)
{
	t_3d_point	pa;
	t_3d_point	ba;
	float		h;

	pa = soustraction_3d_point(p, a);
	ba = soustraction_3d_point(b, a);
	h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
	return (length(soustraction_3d_point(pa, produit_3d_point_par_cst(ba, h)))
		- r);
}

t_capsule	*init_capsule(t_shapes *shapes)
{
	int			i;
	t_capsule	*capsule;

	capsule = malloc(sizeof(t_capsule) * shapes->nmb_capsule);
	i = 0;
	while (i < shapes->nmb_capsule)
	{
		capsule[i].color.r = shapes->capsule[i].color.x;
		capsule[i].color.g = shapes->capsule[i].color.z;
		capsule[i].color.b = shapes->capsule[i].color.y;
		capsule[i].top = shapes->capsule[i].top;
		capsule[i].bottom = shapes->capsule[i].bottom;
		capsule[i].rayon = shapes->capsule[i].diameter / 2;
		i++;
	}
	return (capsule);
}


