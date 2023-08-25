/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:25:16 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/22 00:32:53 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char **str, char **split, char *string, t_shapes *shapes)
{
	if (str)
		free_double_array(str);
	if (split)
		free_double_array(split);
	free (shapes->cylinder);
	free (shapes->sphere);
	free (shapes->plane);
	write (2, "Error\n", 6);
	ft_putstr_fd(string, 2);
	free (shapes);
	exit (1);
}

void	valid_float(char **str, char **split, float *nmb, t_shapes *shapes)
{
	if (str[1] != NULL)
		print_error(str, split, "here0", shapes);
	*nmb = ft_atof(str[0], shapes);
}

void	valid_coordonate(char **str, char **split, t_3d_point *cord, t_shapes *shapes)
{
	if (str[3] != NULL)
		print_error(str, split, "here3", shapes);
	cord->x = ft_atof(str[0], shapes);
	cord->y = ft_atof(str[1], shapes);
	cord->z = ft_atof(str[2], shapes);
}

void	color_range(char **str, char **split, t_3d_point color, t_shapes *shapes)
{
	int	a;
	int	b;
	int	c;

	a = color.x;
	b = color.y;
	c = color.z;
	if (!(a >= 0 && a <= 255) || !(b >= 0 && b <= 255) || !(c >= 0 && c <= 255))
		print_error(str, split, "color_range", shapes);
}

void	valid_normalized_vect(char **str, char **split, t_3d_point vect, t_shapes *shapes)
{
	int	a;
	int	b;
	int	c;

	a = vect.x;
	b = vect.y;
	c = vect.z;
	if (!(a >= -1 && a <= 1) || !(b >= -1 && b <= 1) || !(c >= -1 && c <= 1))
		print_error(str, split, "normalized_vect", shapes);
}
