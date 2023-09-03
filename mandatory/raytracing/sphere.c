/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:51 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:57 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

float	sphere(t_3d_point p, float s)
{
	return (length(p) - s);
}

t_sphere	*init_sphere(t_shapes *shapes)
{
	int			i;
	t_sphere	*sphere;

	i = 0;
	sphere = malloc(sizeof(t_sphere) * shapes->nmb_sp);
	while (i < shapes->nmb_sp)
	{
		sphere[i].color.r = shapes->sphere[i].color.x;
		sphere[i].color.g = shapes->sphere[i].color.z;
		sphere[i].color.b = shapes->sphere[i].color.y;
		sphere[i].centre = shapes->sphere[i].center;
		sphere[i].rayon = shapes->sphere[i].diameter / 2;
		i++;
	}
	return (sphere);
}
