/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:25:16 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/29 01:58:16 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	print_error(char **str, char **split, char *string, t_shapes *shapes)
{
	write (2, "Error\n", 6);
	ft_putstr_fd(string, 2);
	if (str)
		free_double_array(str);
	if (split)
		free_double_array(split);
	if (shapes)
	{
		free (shapes->cylinder);
		free (shapes->sphere);
		free (shapes->plane);
		free (shapes);
	}
	exit (1);
}

void	valid_float(char **str, char **split, float *nmb, t_shapes *shapes)
{
	if (str[1] != NULL)
		print_error(str, split, "not a valid float\n", shapes);
	*nmb = ft_atof(str[0], shapes);
}

void	valid_coordonate(char **s1, char **s2, t_3d_point *cord, t_shapes *sp)
{
	if (s1[3] != NULL)
		print_error(s1, s2, "not a valid coordonate\n", sp);
	cord->x = ft_atof(s1[0], sp);
	cord->y = ft_atof(s1[1], sp);
	cord->z = ft_atof(s1[2], sp);
}

void	color_range(char **s1, char **s2, t_3d_point color, t_shapes *shapes)
{
	int	a;
	int	b;
	int	c;

	a = color.x;
	b = color.y;
	c = color.z;
	if (!(a >= 0 && a <= 255) || !(b >= 0 && b <= 255) || !(c >= 0 && c <= 255))
		print_error(s1, s2, "color_range\n", shapes);
}

void	valid_normalized_vect(char **s1, char **s2, t_3d_point v, t_shapes *sp)
{
	int	a;
	int	b;
	int	c;

	a = v.x;
	b = v.y;
	c = v.z;
	if (!(a >= -1 && a <= 1) || !(b >= -1 && b <= 1) || !(c >= -1 && c <= 1))
		print_error(s1, s2, "normalized_vect\n", sp);
}
