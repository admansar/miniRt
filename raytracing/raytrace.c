/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:49 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:57 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	raymarching(t_all *all, t_3d_point direction)
{
	int			i;
	float		t;
	t_3d_point	pos;
	float		h;

	i = 0;
	t = 0;
	while (i < ITERATION)
	{
		pos = somme_3d_point(all->camera.direction,
				produit_3d_point_par_cst(direction, t));
		h = map(pos, all);
		if (t > T_MAX || h < 1e-4)
			break ;
		t += h;
		i++;
	}
	return (t);
}

// diff[1] is the ambient and diff[2] is the specular
int	raytracing_shape(t_all *all, t_3d_point direction)
{
	t_3d_point	color;
	float		t;
	t_3d_point	pos;
	float		diff[3];
	t_3d_point	norm;

	t = raymarching(all, direction);
	if (!(t <= T_MAX))
		return (0.f);
	pos = somme_3d_point(all->camera.direction,
			produit_3d_point_par_cst(direction, t));
	norm = calcul_normal(pos, all);
	diff[0] = clamp(dot(norm, vec3(0, 1, 0)), 0.f, 1.f);
	diff[0] *= calc_shadow(pos, *all, 0.02, 1.5f);
	diff[1] = (0.5f + 0.5f * dot(norm, all->plan->light.direction));
	diff[2] = powf(clamp(dot(norm,
					vecteur_normalise(soustraction_3d_point
						(all->plan->light.direction, direction))),
				0.0, 1.3), 16.0);
	color = produit_3d_point_par_cst(vec3(diff[1] + diff[0] + diff[2],
				diff[1] + diff[0] + diff[2],
				diff[1] + diff[0] + diff[2]), 
			all->plan->light.lumnosite);
	color = color_multi(color, all->map.color);
	return (rgb_to_int(color.x, color.y, color.z));
}

void	draw_shape(t_all *all, t_data *image)
{
	t_3d_point	direction;
	float		half_fov;
	float		pixel_col;
	float		ndc_x;
	float		ndc_y;

	half_fov = tan(deg_to_rad(all->camera.fov / 2.0));
	all->plan->x = -1;
	while (++all->plan->x < HEIGHT)
	{
		all->plan->y = -1;
		while (++all->plan->y < WIDTH)
		{
			ndc_x = ((2.0f * (all->plan->y + 0.5f) / WIDTH) - 1.0f) 
				* (float)WIDTH / HEIGHT;
			ndc_y = 1.0f - 2.0f * (all->plan->x + 0.5f) / HEIGHT;
			direction = vec3(ndc_x * half_fov, ndc_y * half_fov, 5.f);
			direction = soustraction_3d_point(direction, all->camera.position);
			direction = vecteur_normalise(direction);
			pixel_col = raytracing_shape(all, direction);
			if (pixel_col)
				my_mlx_pixel_put(image, all->plan->y, all->plan->x, pixel_col);
		}
	}
}
