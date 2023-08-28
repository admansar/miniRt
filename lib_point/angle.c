/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:06:02 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:06:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_point.h"
#include <stdio.h>

void	point_printer(t_3d_point a)
{
	printf("(%.1f, %.1f, %.1f)", a.x, a.y, a.z);
}

float	deg_to_rad(float angle_deg)
{
	return ((angle_deg * M_PI) / (180));
}

t_2d_point	spherique_to_iso(t_3d_point a)
{
	t_2d_point	re;
	float		angle_deg;
	float		angle_x;
	float		angle_y;

	angle_deg = 60;
	angle_x = deg_to_rad(angle_deg);
	angle_y = deg_to_rad(90 - angle_deg);
	re.x = (a.x * cos(angle_x)) - (a.y * cos(angle_x));
	re.y = (a.x * sin(angle_y)) + (a.y * sin(angle_y)) - a.z;
	return (re);
}

int	inside_the_cercle(float x, float y, float rayon)
{
	int	dis;

	dis = (pow(x, 2) + pow(y, 2));
	return (dis <= pow(rayon, 2));
}

float	angle_between(t_3d_point u, t_3d_point v)
{
	float	dotproduct;
	float	normu;
	float	normv;
	float	costheta;

	dotproduct = dot(u, v);
	normu = sqrt(dot(u, u));
	normv = sqrt(dot(v, v));
	costheta = dotproduct / (normu * normv);
	return (acos(costheta));
}
