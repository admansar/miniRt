/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 18:09:30 by admansar          #+#    #+#             */
/*   Updated: 2023/08/29 01:45:31 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include <mlx.h>

# include "gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <limits.h>
# include "libft/libft.h"
# include "lib_point/lib_point.h"
# include "raytracing/material.h"

typedef struct s_light_info
{
	t_3d_point	orig;
	t_3d_point	ray;
	float		light_bright;
	int			nmb;
}	t_light_info;

typedef struct s_camera_info
{
	t_3d_point	orig;
	t_3d_point	ray;
	t_3d_point	norm_vect;
	float		fov;
	int			nmb;
}	t_camera_info;

typedef struct s_sphere_info
{
	t_3d_point	center;
	t_3d_point	color;
	float		diameter;
	int			nmb;
}	t_sphere_info;

typedef struct s_cylinder_info
{
	t_3d_point	centre;
	t_3d_point	norm_vect;
	t_3d_point	color;
	float		diameter;
	float		height;
	int			nmb;
}	t_cylinder_info;

typedef struct s_ambient_info
{
	float		ratio;
	t_3d_point	color;
	int			nmb;
}	t_ambient_info;

typedef struct s_plane_info
{
	t_3d_point	point;
	t_3d_point	norm_vect;
	t_3d_point	color;
	int			nmb;
}	t_plane_info;

typedef struct s_shapes
{
	int				nmb_cy;
	int				nmb_sp;
	int				nmb_plane;
	t_camera_info	camera;
	t_light_info	light;
	t_ambient_info	ambient;
	t_sphere_info	*sphere;
	t_plane_info	*plane;
	t_cylinder_info	*cylinder;
	t_all			*all;
}	t_shapes;

// check_file_rt file
void	init_shape(t_shapes *shapes);
void	initiaize_numbers_of_shapes(t_shapes *shapes);
char	*read_from_file(t_shapes *shapes, int fd);
int		check_file(char **av, t_shapes *shapes);
//check_shapes_sequel_two file
void	check_sphere_sequel(t_shapes *shapes, char **str, char **split, int i);
void	check_sphere(t_shapes *shapes, char **split);
void	check_plane_sequel(t_shapes *shapes, char **str, char **split, int i);
void	check_plane(t_shapes *shapes, char **split);
//check_shapes_sequel file
void	check_ambient(t_shapes *shapes, char **split);
void	check_camera_sequel(t_shapes *shapes, char **str, char **split);
void	check_camera(t_shapes *shapes, char **split);
void	check_light(t_shapes *shapes, char **split);
//check_shapes file
void	check_cylinder_sequel(char **s1, char **s2, t_shapes *shapes, int i);
void	check_cylinder(t_shapes *shapes, char **split);
void	shapes_fnct(t_shapes *shapes, char **split);
//check_validation file
void	print_error(char **str, char **split, char *string, t_shapes *shapes);
void	valid_float(char **str, char **split, float *nmb, t_shapes *shapes);
void	valid_coordonate(char **s1, char **s2, t_3d_point *cord, t_shapes *sp);
void	color_range(char **s1, char **s2, t_3d_point color, t_shapes *shapes);
void	valid_normalized_vect(char **s1, char **s2, t_3d_point v, t_shapes *sp);
// ft_atof file
int		help(void);
int		ft_strncmp_dual(const char *s1, const char *s2, size_t n);
double	_continue(int i, char *str, t_shapes *shapes);
void	ft_atof_sequel(char *str, int *i, long int *d);
double	ft_atof(char *str, t_shapes *shapes);
//minirt_split file
char	**minirt_split(char *s);
void	free_shapes(t_shapes *shapes);
//parcing file
void	free_double_array(char **c);
void	calcul_nmb_sequel(t_shapes *shapes, char *all);
void	calcul_nmbr_of_shapes(char *all, t_shapes *shapes);
//minirt file
void	minirt(t_shapes *shapes);
#endif
