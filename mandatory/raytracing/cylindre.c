/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:36 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:56 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	get_cy_dist(t_define_cylindre *cylinder)
{
	float	re;

	if (fmax(cylinder->x, cylinder->y) < 0.f)
		re = -fmin(cylinder->x2, cylinder->y2);
	else
	{
		if (cylinder->x > 0.f)
			re = cylinder->x2;
		else
			re = 0.f;
		if (cylinder->y > 0.0)
			re += cylinder->y2;
	}
	return (re);
}

float	the_cylindre(t_3d_point p, t_3d_point a, t_3d_point b, float r)
{
	t_define_cylindre	cylinder;

	cylinder.ba = soustraction_3d_point(b, a);
	cylinder.pa = soustraction_3d_point(p, a);
	cylinder.baba = dot(cylinder.ba, cylinder.ba);
	cylinder.paba = dot(cylinder.pa, cylinder.ba);
	cylinder.x = length(soustraction_3d_point(produit_3d_point_par_cst
				(cylinder.pa, cylinder.baba), produit_3d_point_par_cst(
					cylinder.ba, cylinder.paba))) - r * cylinder.baba;
	cylinder.y = fabs(cylinder.paba - cylinder.baba * 0.5) - cylinder.baba
		* 0.5;
	cylinder.x2 = cylinder.x * cylinder.x;
	cylinder.y2 = cylinder.y * cylinder.y * cylinder.baba;
	cylinder.d = get_cy_dist(&cylinder);
	if (cylinder.d > 0)
		cylinder.sign = 1;
	else
		cylinder.sign = -1;
	return (cylinder.sign * sqrtf(fabs(cylinder.d)) / cylinder.baba);
}

void	cylindre_bottom(t_cylinder *cylinder)
{
	cylinder->top = somme_3d_point(cylinder->position,
			produit_3d_point_par_cst(cylinder->normal,
				0.5f * cylinder->hauteur));
	cylinder->bottom = soustraction_3d_point(cylinder->position,
			produit_3d_point_par_cst(cylinder->normal,
				0.5f * cylinder->hauteur));
}

t_cylinder	*init_cylinder(t_shapes *shapes)
{
	t_cylinder	*cylinder;
	int			i;

	cylinder = malloc(sizeof(t_cylinder) * shapes->nmb_cy);
	i = 0;
	while (i < shapes->nmb_cy)
	{
		cylinder[i].color.r = shapes->cylinder[i].color.x;
		cylinder[i].color.g = shapes->cylinder[i].color.z;
		cylinder[i].color.b = shapes->cylinder[i].color.y;
		cylinder[i].position = shapes->cylinder[i].centre;
		cylinder[i].rayon = shapes->cylinder[i].diameter / 2;
		cylinder[i].hauteur = shapes->cylinder[i].height;
		cylinder[i].normal = shapes->cylinder[i].norm_vect;
		cylindre_bottom(&cylinder[i]);
		i++;
	}
	return (cylinder);
}
