/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes_sequel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:27:39 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/28 12:27:20 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

void	check_camera_sequel(t_shapes *shapes, char **str, char **split)
{
	valid_float(str, split, &shapes->camera.fov, shapes);
	if (!(shapes->camera.fov >= 0 && shapes->camera.fov <= 180))
		print_error(str, split, "check your camera fov\n", shapes);
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
			check_camera_sequel(shapes, str, split);
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
