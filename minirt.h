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

#ifndef WIDTH_HEIGHT
#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 1000
#endif
#define RATIO (float)WIDTH / (float)HEIGHT
#endif 

#ifndef T_MAX
#define T_MAX 2.f
#endif

#ifndef ITERATION
#define ITERATION 200
#endif

#ifndef EPSILON
#define EPSILON 0.001
#endif

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

typedef struct s_capsule_info
{
	t_3d_point	top;
	t_3d_point	bottom;
	float		diameter;
	t_3d_point	color;
	int			nmb;
}	t_capsule_info;


typedef	struct	s_mlx
{
	void *init;
	void *win;
}				t_mlx;

typedef struct s_2d_point
{
	float x;
	float y;
}				t_2d_point;

typedef struct s_light
{
	t_3d_point	direction;
	float		lumnosite;
	float		ambient;
}			t_light;

typedef	struct	s_espace
{
	float	x;
	float	y;
	float	z;
	t_light	light;
	float	centre_screen_x;
	float	centre_screen_y;
}				t_espace;

typedef struct s_normal_info
{
	t_2d_point e;
	t_3d_point v1;
	t_3d_point v2;
	t_3d_point v3;
	t_3d_point v4;
	t_3d_point a1;
	t_3d_point a2;
	t_3d_point a3;
	t_3d_point a4;
	t_3d_point re;
}			t_normal_info;

typedef struct s_define_cylindre
{
	t_3d_point ba;
	t_3d_point pa;
	float baba;
	float paba;
	float x;
	float y;
	float x2;
	float y2;
	float d;
	float sign;

} t_define_cylindre;



typedef struct s_map
{
	float	min;
	t_rgb	color;
}			t_map;



typedef	struct	s_plan
{
	float		x;
	float		y;
	float		z;
	t_3d_point	position;
	t_3d_point 	normal;
	t_rgb		color;
	t_light		light;
	float		centre_screen_x;
	float		centre_screen_y;
}				t_plan;

typedef struct	s_cercle
{
	float	rayon;
	float	color;
	float	centre_x;
	float	centre_y;
}				t_cercle;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}                t_data;

typedef struct s_sphere
{
	t_3d_point	centre;
	float		rayon;
	t_rgb		color;
}				t_sphere;

typedef struct s_camera
{
	t_3d_point	position;
	t_3d_point	direction;
	float		fov;
	int			nmb;
}				t_camera;

typedef struct s_cylinder
{
    t_rgb		color;
    t_3d_point	position;
    t_3d_point	normal;
    float		rayon;
	t_3d_point	top;
	t_3d_point	bottom;
    float		hauteur;     
}				t_cylinder;

typedef struct s_capsule
{
	t_3d_point	top;
	t_3d_point	bottom;
	t_rgb	color;
	float		rayon;
}	t_capsule;

typedef struct s_all
{
	t_mlx		mlx;
	t_plan		*plan;
	t_data		image;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_capsule	*capsule;
	t_camera	camera;
	t_map		map;
	int			nmb_sp;
	int			nmb_capsule;
	int			nmb_plan;
	int			nmb_cy;
	int			nmb_shape;
	int			holder[3];
}			t_all;

typedef struct s_shapes
{
	int				nmb_cy;
	int				nmb_sp;
	int				nmb_plane;
	int				nmb_capsule;
	t_camera_info	camera;
	t_light_info	light;
	t_ambient_info	ambient;
	t_sphere_info	*sphere;
	t_plane_info	*plane;
	t_cylinder_info	*cylinder;
	t_capsule_info		*capsule;
	t_all			*all;
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

void point_printer(t_3d_point a);
void	print_color(t_rgb color);
void	print_cylinders(t_shapes *shapes);
void	print_capsules(t_shapes *shapes);
void	print_spheres(t_shapes *shapes);
void	print_planes(t_shapes *shapes);
void	print_everything(t_shapes *shapes);
#endif
