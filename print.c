/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 18:47:40 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/27 00:28:04 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_color(t_rgb color)
{
	printf("%.1f %.1f %.1f", color.r, color.g, color.b);
}

void	print_cylinders(t_shapes *shapes)
{
	int	i;

	i  = 0;
	while (i < shapes->nmb_cy)
	{
	printf("cylinder\t");
		point_printer(shapes->cylinder[i].centre);
		point_printer(shapes->cylinder[i].norm_vect);
		printf("%.1f %.1f", shapes->cylinder[i].diameter, shapes->cylinder[i].height);
		point_printer(shapes->cylinder[i].color);
		i++;
		printf("\n\n");
	}
}

void	print_capsules(t_shapes *shapes)
{
	int	i;

	i  = 0;
	while (i < shapes->nmb_capsule)
	{
	printf("capsule\t");
		point_printer(shapes->capsule[i].top);
		point_printer(shapes->capsule[i].bottom);
		printf("%.1f %.1f", shapes->capsule[i].diameter, shapes->capsule[i].diameter);
		point_printer(shapes->capsule[i].color);
		i++;
	printf("\n\n");
	}
}

void	print_spheres(t_shapes *shapes)
{
	int	i;
 
	i  = 0;
	printf("sphere\t");
	while (i < shapes->nmb_sp)
	{
		point_printer(shapes->sphere[i].center);
		printf("%.1f", shapes->sphere[i].diameter);
		point_printer(shapes->sphere[i].color);
		i++;
	}
	printf("\n\n");
}

void	print_planes(t_shapes *shapes)
{
	int	i;

	i  = 0;
	while (i < shapes->nmb_plane)
	{
		printf("plane\t");
		point_printer(shapes->plane[i].point);
		point_printer(shapes->plane[i].norm_vect);
		point_printer(shapes->plane[i].color);
		i++;
		printf("\n\n");
	}
}

void	print_everything(t_shapes *shapes)
{
	print_cylinders(shapes);
	print_capsules(shapes);
	print_planes(shapes);
	print_spheres(shapes);
	// print_light(shapes);
	// print_camera(shapes);
	// print_ambient(shapes);
}