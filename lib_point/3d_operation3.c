/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_operation3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:05:55 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:06:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib_point.h"

float	norm_euclidienne_3d(t_3d_point vecteur)
{
	float	re;

	re = powf(vecteur.x, 2) + powf(vecteur.y, 2) + powf(vecteur.z, 2);
	return (sqrtf(re));
}

float	dot(t_3d_point v1, t_3d_point v2)
{
	return (((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z)));
}

t_3d_point	vecteur_normalise(t_3d_point vecteur)
{
	t_3d_point	re;
	float		norm_euc;

	norm_euc = norm_euclidienne_3d(vecteur);
	re.x = vecteur.x / norm_euc;
	re.y = vecteur.y / norm_euc;
	re.z = vecteur.z / norm_euc;
	return (re);
}

t_3d_point	produit_3d_point_par_cst(t_3d_point point, const float cst)
{
	point.x *= cst;
	point.y *= cst;
	point.z *= cst;
	return (point);
}
