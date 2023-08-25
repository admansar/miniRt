#ifndef MINIRT_H
# define MINIRT_H
#include <mlx.h>

# include "gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_3d_point
{
	float x;
	float y;
	float z;
}				t_3d_point;

typedef struct s_rgb
{
	float	r;
	float	b;
	float	g;
}				t_rgb;

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
}	t_sphere_info;

typedef struct s_cylinder_info
{
	t_3d_point	centre;
	t_3d_point	norm_vect;
	t_3d_point	color;
	float		diameter;
	float		height;
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
}	t_shapes;
void	minirt(t_shapes *shapes);
char	**minirt_split(char *s);
double	ft_atof(char *str, t_shapes *shapes);
//check_shapes file 
void	check_cylinder_sequel(char **str, char **split, t_shapes *shapes, int i);
void	check_cylinder(t_shapes *shapes, char **split);
void	shapes_fnct(t_shapes *shapes, char **split);
void	initiaize_numbers_of_shapes(t_shapes *shapes);
//check_shapes_sequel file
void	check_ambient(t_shapes *shapes, char **split);
void	check_camera(t_shapes *shapes, char **split);
void	check_light(t_shapes *shapes, char **split);
void	check_sphere(t_shapes *shapes, char **split);
void	check_plane(t_shapes *shapes, char **split);
//check_validation file
void	print_error(char **str, char **split, char *string, t_shapes *shapes);
void	valid_float(char **str, char **split, float *nmb, t_shapes *shapes);
void	valid_coordonate(char **str, char **split, t_3d_point *cord, t_shapes *shapes);
void	color_range(char **str, char **split, t_3d_point color, t_shapes *shapes);
void	valid_normalized_vect(char **str, char **split, t_3d_point vect, t_shapes *shapes);
//parcing file
void	free_double_array(char **c);


//
void	free_shapes(t_shapes *shapes);
//dalete_me
void check_leaks(void);
#endif