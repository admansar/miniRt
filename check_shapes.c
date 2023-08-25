/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:26:59 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/22 01:36:59 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_cylinder_sequel(char **str, char **split, t_shapes *shapes, int i)
{
	if (i == 3)
		valid_float(str, split, &shapes->cylinder->diameter, shapes);
	if (i == 4)
		valid_float(str, split, &shapes->cylinder->height, shapes);
	if (i == 5)
	{
		valid_coordonate(str, split, &shapes->cylinder->color, shapes);
		color_range(str, split, shapes->cylinder->color, shapes);
	}
}

void	check_cylinder(t_shapes *shapes, char **split)
{
	int		i;
	char	**str;

	i = 1;
	if (split[6] != NULL)
		print_error(NULL, split, "here8", shapes);
	while (i <= 5)
	{
		str = ft_split(split[i], ',');
		if (i == 1)
			valid_coordonate(str, split, &shapes->cylinder->centre, shapes);
		if (i == 2)
		{
			valid_coordonate(str, split, &shapes->cylinder->norm_vect, shapes);
			valid_normalized_vect(str, split, shapes->cylinder->norm_vect, shapes);
		}
		check_cylinder_sequel(str, split, shapes, i);
		free_double_array(str);
		str = NULL;
		i++;
	}
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
		print_error(NULL, split, "invalid element", shapes);
}

void	initiaize_numbers_of_shapes(t_shapes *shapes)
{
	shapes->cylinder = NULL;
	shapes->plane = NULL;
	shapes->sphere = NULL;
	shapes->ambient.nmb = 0;
	shapes->light.nmb = 0;
	shapes->camera.nmb = 0;
	shapes->nmb_cy = 0;
	shapes->nmb_sp = 0;
	shapes->nmb_plane = 0;
}
