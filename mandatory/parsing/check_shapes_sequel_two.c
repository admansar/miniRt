/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes_sequel_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:22:58 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/28 12:24:20 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
