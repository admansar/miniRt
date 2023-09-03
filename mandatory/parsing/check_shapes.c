/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:26:59 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/28 19:43:40 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	check_cylinder_sequel(char **str, char **split, t_shapes *shapes, int i)
{
	if (i == 2)
	{
		valid_coordonate(str, split, &shapes->\
		cylinder[shapes->cylinder->nmb].norm_vect, shapes);
		valid_normalized_vect(str, split, shapes->\
		cylinder[shapes->cylinder->nmb].norm_vect, shapes);
	}
	else if (i == 3)
		valid_float(str, split, &shapes->\
		cylinder[shapes->cylinder->nmb].diameter, shapes);
	else if (i == 4)
		valid_float(str, split, &shapes->\
		cylinder[shapes->cylinder->nmb].height, shapes);
	else if (i == 5)
	{
		valid_coordonate(str, split, &shapes->\
		cylinder[shapes->cylinder->nmb].color, shapes);
		color_range(str, split, shapes->\
		cylinder[shapes->cylinder->nmb].color, shapes);
	}
}

void	check_cylinder(t_shapes *shapes, char **split)
{
	int			i;
	char		**str;
	t_3d_point	*p;

	i = 1;
	p = &shapes->cylinder[shapes->cylinder->nmb].centre;
	if (split[6] != NULL)
		print_error(NULL, split, "check your cylinder\n", shapes);
	while (i <= 5)
	{
		str = ft_split(split[i], ',');
		if (i == 1)
			valid_coordonate(str, split, p, shapes);
		check_cylinder_sequel(str, split, shapes, i);
		free_double_array(str);
		str = NULL;
		i++;
	}
	shapes->cylinder->nmb++;
}

/******************************* free shapes **/

void	shapes_fnct(t_shapes *shapes, char **split)
{
	if (split == NULL)
		return ;
	else if (ft_strncmp(split[0], "A", ft_strlen(split[0])) == 0)
		check_ambient(&(*shapes), split);
	else if (ft_strncmp(split[0], "C", ft_strlen(split[0])) == 0)
		check_camera(&(*shapes), split);
	else if (ft_strncmp(split[0], "L", ft_strlen(split[0])) == 0)
		check_light(&(*shapes), split);
	else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
		check_sphere(&(*shapes), split);
	else if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
		check_plane(&(*shapes), split);
	else if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
		check_cylinder(&(*shapes), split);
	else
		print_error(NULL, split, "invalid element\n", shapes);
}
