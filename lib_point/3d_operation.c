/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:05:51 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:06:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_point.h"

t_3d_point	somme_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point	re;

	re.x = a.x + b.x;
	re.y = a.y + b.y;
	re.z = a.z + b.z;
	return (re);
}

t_3d_point	produit_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point	re;

	re.x = a.x * b.x;
	re.y = a.y * b.y;
	re.z = a.z * b.z;
	return (re);
}

t_3d_point	soustraction_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point	re;

	re.x = a.x - b.x;
	re.y = a.y - b.y;
	re.z = a.z - b.z;
	return (re);
}

t_3d_point	vec3(float x, float y, float z)
{
	t_3d_point	re;

	re.x = x;
	re.y = y;
	re.z = z;
	return (re);
}
