/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_operation2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:05:53 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:06:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_point.h"

t_3d_point	cross(t_3d_point a, t_3d_point b)
{
	return (vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x
				* b.y) - (a.y * b.x)));
}

float	distance_3d_point(t_3d_point a, t_3d_point b)
{
	float	re;

	re = sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (re);
}

float	norm_carre_3d_point(t_3d_point a, t_3d_point b)
{
	float	re;

	re = (pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (re);
}

t_3d_point	reflect(t_3d_point in, t_3d_point normal)
{
	t_3d_point	reflection;
	float		dotp;

	dotp = dot(in, normal);
	reflection.x = in.x - (2.f * dotp * normal.x);
	reflection.y = in.y - (2.f * dotp * normal.y);
	reflection.z = in.z - (2.f * dotp * normal.z);
	return (reflection);
}
