/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes_sequel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:27:39 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/27 16:46:04 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_ambient(t_shapes *shapes, char **split)
{
	int		i;
	char	**str;

	i = 1;
	if (split == NULL)
		return ;
	if (split[3] != NULL)
		print_error(NULL, split, "check your ambient\n", shapes);
	while (i <= 2)
	{
		str = ft_split(split[i], ',');
		if (i == 1)
			valid_float(str, split, &shapes->ambient.ratio, shapes);
		else
		{
			valid_coordonate(str, split, &shapes->ambient.color, shapes);
			color_range(str, split, shapes->ambient.color, shapes);
		}
		free_double_array(str);
		str = NULL;
		i++;
	}
	shapes->ambient.nmb++;
}

void	check_camera(t_shapes *shapes, char **split)
{
	int		i;
	char	**str;

	i = 1;
	if (split[4] != NULL)
		print_error(NULL, split, "check your camera\n", shapes);
	while (i <= 3)
	{
		str = ft_split(split[i], ',');
		if (i == 1)
			valid_coordonate(str, split, &shapes->camera.orig, shapes);
		if (i == 2)
		{
			valid_coordonate(str, split, &shapes->camera.norm_vect, shapes);
			valid_normalized_vect(str, split, shapes->camera.norm_vect, shapes);
		}
		if (i == 3)
		{
			valid_float(str, split, &shapes->camera.fov, shapes);
			if (!(shapes->camera.fov >= 0 && shapes->camera.fov <= 180))
				print_error(str, split, "check your camera fov\n", shapes);
		}
		free_double_array(str);
		str = NULL;
		i++;
	}
	shapes->camera.nmb++;
}

void	check_light(t_shapes *shapes, char **split)
{
	int		i;
	char	**str;
	float	light_bright;

	i = 1;
	light_bright = shapes->light.light_bright;
	if (split[4] != NULL )
		print_error(NULL, split, "check your light\n", shapes);
	while (i <= 3)
	{
		str = ft_split(split[i], ',');
		if (i == 1)
			valid_coordonate(str, split, &shapes->light.orig, shapes);
		if (i == 2)
		{
			valid_float(str, split, &shapes->light.light_bright, shapes);
			if (!(shapes->light.light_bright >= 0 && shapes->\
			light.light_bright <= 1))
				print_error(str, split, "check your light brightness\n", shapes);
		}
		free_double_array(str);
		str = NULL;
		i++;
	}
	shapes->light.nmb++;
}

void	check_sphere_sequel(t_shapes *shapes, char **str, char **split, int i)
{
	t_3d_point	*a;
	float		*b;
	t_3d_point	*c;

	a = &shapes->sphere[shapes->sphere->nmb].center;
	b = &shapes->sphere[shapes->sphere->nmb].diameter;
	c = &shapes->sphere[shapes->sphere->nmb].color;
	if (i == 1)
		valid_coordonate(str, split, a, shapes);
	if (i == 2)
		valid_float(str, split, b, shapes);
	if (i == 3)
	{
		valid_coordonate(str, split, c, shapes);
		color_range(str, split, *c, shapes);
	}
}

void	check_sphere(t_shapes *shapes, char **split)
{
	int		i;
	char	**str;

	i = 1;
	if (split[4] != NULL)
		print_error(NULL, split, "check your sphere\n", shapes);
	while (i <= 3)
	{
		str = ft_split(split[i], ',');
		check_sphere_sequel(shapes, str, split, i);
		free_double_array(str);
		str = NULL;
		i++;
	}
	shapes->sphere->nmb++;
}

void	check_plane_sequel(t_shapes *shapes, char **str, char **split, int i)
{
	t_3d_point	*a;
	t_3d_point	*b;
	t_3d_point	*c;

	a = &shapes->plane[shapes->plane->nmb].point;
	b = &shapes->plane[shapes->plane->nmb].norm_vect;
	c = &shapes->plane[shapes->plane->nmb].color;
	if (i == 1)
		valid_coordonate(str, split, a, shapes);
	if (i == 2)
	{
		valid_coordonate(str, split, b, shapes);
		valid_normalized_vect(str, split, *b, shapes);
	}
	if (i == 3)
	{
		valid_coordonate(str, split, c, shapes);
		color_range(str, split, *c, shapes);
	}
}

void	check_plane(t_shapes *shapes, char **split)
{
	int		i;
	char	**str;

	i = 1;
	if (split[4] != NULL)
		print_error(NULL, split, "check your plane\n", shapes);
	while (i <= 3)
	{
		str = ft_split(split[i], ',');
		check_plane_sequel(shapes, str, split, i);
		free_double_array(str);
		str = NULL;
		i++;
	}
	shapes->plane->nmb++;
}
