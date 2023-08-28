/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_point.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:06:04 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:06:07 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_POINT_H
# define LIB_POINT_H

# include <math.h>

typedef struct s_2d_point
{
	float	x;
	float	y;
}			t_2d_point;

typedef struct s_3d_point
{
	float	x;
	float	y;
	float	z;
}			t_3d_point;
float		dot(t_3d_point v1, t_3d_point v2);
float		clamp(float a, float min, float max);
t_3d_point	project_to_3d(t_2d_point point_2d);
float		length2d(t_2d_point a);
float		length(t_3d_point v);
t_3d_point	produit_3d_point_par_cst(t_3d_point point, const float cst);
t_3d_point	vecteur_normalise(t_3d_point vecteur);
float		norm_euclidienne_3d(t_3d_point vecteur);
t_3d_point	iso_to_cart(t_2d_point input);
int			inside_the_cercle(float x, float y, float rayon);
t_2d_point	spherique_to_iso(t_3d_point a);
float		deg_to_rad(float angle_deg);
t_3d_point	reflect(t_3d_point in, t_3d_point normal);
float		norm_carre_3d_point(t_3d_point a, t_3d_point b);
float		distance_3d_point(t_3d_point a, t_3d_point b);
t_3d_point	soustraction_3d_point(t_3d_point a, t_3d_point b);
void		point_printer(t_3d_point a);
t_3d_point	cross(t_3d_point a, t_3d_point b);
t_3d_point	vec3(float x, float y, float z);
t_3d_point	produit_3d_point(t_3d_point a, t_3d_point b);
t_3d_point	somme_3d_point(t_3d_point a, t_3d_point b);
float		angle_between(t_3d_point u, t_3d_point v);

#endif
