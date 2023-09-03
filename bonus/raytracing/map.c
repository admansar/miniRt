/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:43 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:56 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	checking_shape(t_3d_point pos, t_all *all, int i, float *re)
{
	if (i < all->holder[0])
		re[i] = sphere(soustraction_3d_point(pos, all->sphere[i].centre),
				all->sphere[i].rayon);
	else if (i < all->holder[1])
		re[i] = the_cylindre(pos, all->cylinder[i - all->holder[0]].top,
				all->cylinder[i - all->holder[0]].bottom, all->cylinder[i
				- all->holder[0]].rayon);
	else if (i < all->holder[2])
		re[i] = plane(soustraction_3d_point(pos, all->plan[i
					- all->holder[1]].position), all->plan[i
				- all->holder[1]].normal, 0.f);
	else
		re[i] = sdcapsule(pos, all->capsule[i - all->holder[2]].top,
				all->capsule[i - all->holder[2]].bottom, all->capsule[i
				- all->holder[2]].rayon);
}

float	map(t_3d_point pos, t_all *all)
{
	float	*re;
	int		i;
	float	min;

	re = malloc(sizeof(float) * (all->nmb_shape));
	min = T_MAX;
	i = -1;
	while (++i < all->nmb_shape)
		checking_shape(pos, all, i, re);
	i = min_tab_index(re, all->nmb_shape);
	min = re[i];
	if (i < all->nmb_sp)
		all->map.color = all->sphere[i].color;
	else if (i < all->nmb_sp + all->nmb_cy && i >= all->nmb_sp)
		all->map.color = all->cylinder[i - all->holder[0]].color;
	else if (i >= all->nmb_sp + all->nmb_cy && i < all->nmb_sp + all->nmb_cy
		+ all->nmb_plan)
		all->map.color = all->plan[i - all->holder[1]].color;
	else
		all->map.color = all->capsule[i - all->holder[2]].color;
	free(re);
	return (min);
}

t_3d_point	calcul_normal(t_3d_point pos, t_all *all)
{
	t_normal_info	normal;

	normal.e.x = 0.5f;
	normal.e.y = -0.5f;
	normal.v1 = vec3(normal.e.x, normal.e.y, normal.e.y);
	normal.v2 = vec3(normal.e.y, normal.e.y, normal.e.x);
	normal.v3 = vec3(normal.e.y, normal.e.x, normal.e.y);
	normal.v4 = vec3(normal.e.x, normal.e.x, normal.e.x);
	normal.a1 = produit_3d_point_par_cst(normal.v1, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v1, EPSILON)), all));
	normal.a2 = produit_3d_point_par_cst(normal.v2, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v2, EPSILON)), all));
	normal.a3 = produit_3d_point_par_cst(normal.v3, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v3, EPSILON)), all));
	normal.a4 = produit_3d_point_par_cst(normal.v4, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v4, EPSILON)), all));
	normal.re = vecteur_normalise(somme_3d_point(somme_3d_point(normal.a1,
					normal.a2), somme_3d_point(normal.a3, normal.a4)));
	return (normal.re);
}

float	calc_shadow(t_3d_point pos, t_all all, float mint, float tmax)
{
	float	re;
	float	t;
	float	s;
	float	h;
	int		i;

	i = 0;
	re = 1.0;
	t = mint;
	while (i < 25)
	{
		h = map(somme_3d_point(pos,
					produit_3d_point_par_cst(all.plan->light.direction,
						t)), &all);
		s = clamp(10.0 * h / t, 0.0, 1.0);
		re = fmin(re, s);
		t += clamp(h, 0.01, 0.2);
		if (re < 0.004 || t > tmax)
			break ;
	}
	return (re);
}
