/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:44 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 19:44:23 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# ifndef WIDTH_HEIGHT
#  ifndef WIDTH
#   define WIDTH 1200
#  endif
#  ifndef HEIGHT
#   define HEIGHT 1000
#  endif
# endif

# ifndef T_MAX
#  define T_MAX 2.f
# endif

# ifndef ITERATION
#  define ITERATION 200
# endif

# ifndef EPSILON
#  define EPSILON 0.001
# endif

# include "../lib_point/lib_point.h"

typedef struct s_rgb
{
	float				r;
	float				b;
	float				g;
}						t_rgb;
typedef struct s_mlx
{
	void				*init;
	void				*win;
}						t_mlx;

typedef struct s_light
{
	t_3d_point			direction;
	float				lumnosite;
	float				ambient;
}						t_light;

typedef struct s_espace
{
	float				x;
	float				y;
	float				z;
	t_light				light;
	float				centre_screen_x;
	float				centre_screen_y;
}						t_espace;

typedef struct s_normal_info
{
	t_2d_point			e;
	t_3d_point			v1;
	t_3d_point			v2;
	t_3d_point			v3;
	t_3d_point			v4;
	t_3d_point			a1;
	t_3d_point			a2;
	t_3d_point			a3;
	t_3d_point			a4;
	t_3d_point			re;
}						t_normal_info;

typedef struct s_define_cylindre
{
	t_3d_point			ba;
	t_3d_point			pa;
	float				baba;
	float				paba;
	float				x;
	float				y;
	float				x2;
	float				y2;
	float				d;
	float				sign;

}						t_define_cylindre;

typedef struct s_map
{
	float				min;
	t_rgb				color;
}						t_map;

typedef struct s_plan
{
	float				x;
	float				y;
	float				z;
	t_3d_point			position;
	t_3d_point			normal;
	t_rgb				color;
	t_light				light;
	float				centre_screen_x;
	float				centre_screen_y;
}						t_plan;

typedef struct s_cercle
{
	float				rayon;
	float				color;
	float				centre_x;
	float				centre_y;
}						t_cercle;

typedef struct s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;

typedef struct s_sphere
{
	t_3d_point			centre;
	float				rayon;
	t_rgb				color;
}						t_sphere;

typedef struct s_camera
{
	t_3d_point			position;
	t_3d_point			direction;
	float				fov;
	int					nmb;
}						t_camera;

typedef struct s_cylinder
{
	t_rgb				color;
	t_3d_point			position;
	t_3d_point			normal;
	float				rayon;
	t_3d_point			top;
	t_3d_point			bottom;
	float				hauteur;
}						t_cylinder;

typedef struct s_all
{
	t_mlx				mlx;
	t_plan				*plan;
	t_data				image;
	t_sphere			*sphere;
	t_cylinder			*cylinder;
	t_camera			camera;
	t_map				map;
	int					nmb_sp;
	int					nmb_plan;
	int					nmb_cy;
	int					nmb_shape;
	int					holder[3];
}						t_all;

typedef struct s_shapes	t_shapes;

void					minirt(t_shapes *shapes);
void					init_shapes(t_shapes *shapes, t_all *all);
t_camera				init_camera(t_shapes *shapes);
t_cylinder				*init_cylinder(t_shapes *shapes);
t_plan					*init_plan(t_shapes *shapes);
t_sphere				*init_sphere(t_shapes *shapes);
int						red_buttom(t_shapes *shapes);
int						escupe_fnct(int keycode, t_shapes *shapes);
void					free_all(t_all *all);
void					free_shapes(t_shapes *shapes);
void					cylindre_bottom(t_cylinder *cylinder);
int						rgb_to_int(int r, int g, int b);
void					stay_a_color(int *color);
void					draw_shape(t_all *all, t_data *image);
int						raytracing_shape(t_all *all, t_3d_point direction);
float					raymarching(t_all *all, t_3d_point direction);
float					calc_shadow(t_3d_point pos, t_all all, float mint,
							float tmax);
t_3d_point				calcul_normal(t_3d_point pos, t_all *all);
t_3d_point				color_multi(t_3d_point a, t_rgb color);
float					map(t_3d_point pos, t_all *all);
void					checking_shape(t_3d_point pos, t_all *all, int i,
							float *re);
int						min_tab_index(float *tab, int size);
float					plane(t_3d_point p, t_3d_point n, float h);
float					sphere(t_3d_point p, float s);
float					the_cylindre(t_3d_point p, t_3d_point a, t_3d_point b,
							float r);
float					get_cy_dist(t_define_cylindre *cylinder);
void					my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
