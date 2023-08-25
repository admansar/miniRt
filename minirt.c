#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minirt.h"

#ifndef WIDTH_HEIGHT
#ifndef WIDTH
#define WIDTH 1000
#endif
#ifndef HEIGHT
#define HEIGHT 1000
#endif
#define RATIO (float)WIDTH / HEIGHT
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

typedef struct s_intersection
{
	float x1;
	float x2;
	float min;
	t_3d_point hiting_point;
	t_3d_point normal_vect;
}			t_intersection;

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



typedef struct s_all
{
	t_mlx		mlx;
	t_plan		plan;
	t_data		image;
	t_sphere	*sphere;
	t_cylinder	cylinder;
	t_camera	camera;
	t_map		map;
	int			nmb_sp;
	int			nmb_plan;
	int			nmb_cy;
	int			nmb_shape;
}			t_all;

float dot(t_3d_point v1, t_3d_point v2);
int inside_the_cercle (float x, float y, float rayon);
int inside_sphere(t_3d_point point, t_sphere sphere);
int intersectplan(t_plan plan, t_camera camera, t_3d_point point);
int rgb_to_int(int r, int g, int b);
/************************************/
/*		OPERATION FOR 3D POINTS		*/
/************************************/

t_3d_point somme_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point re;

	re.x = a.x + b.x;
	re.y = a.y + b.y;
	re.z = a.z + b.z;
	return (re);
}

t_3d_point produit_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point re;

	re.x = a.x * b.x;
	re.y = a.y * b.y;
	re.z = a.z * b.z;
	return (re);
}

t_3d_point vec3(float x, float y, float z)
{
	t_3d_point re;

	re.x = x;
	re.y = y;
	re.z = z;
	return (re);
}


t_3d_point cross(t_3d_point a, t_3d_point b)
{
	return (vec3 ((a.y * b.z) - (a.z * b.y),
			   	(a.z * b.x) - (a.x * b.z),
			   	(a.x * b.y) - (a.y * b.x)));
}


void point_printer(t_3d_point a)
{
	printf ("(%f, %f, %f)\n", a.x, a.y, a.z);
}


t_3d_point soustraction_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point re;

	re.x = a.x - b.x;
	re.y = a.y - b.y;
	re.z = a.z - b.z;
	return (re);
}

float distance_3d_point(t_3d_point a, t_3d_point b)
{
	float re;

	re = sqrtf (pow (a.x - b.x, 2) + pow (a.y - b.y, 2) + pow (a.z - b.z, 2));
	return (re);
}

float norm_carre_3d_point(t_3d_point a, t_3d_point b)
{
	float re;

	re = (pow (a.x - b.x, 2) + pow (a.y - b.y, 2) + pow (a.z - b.z, 2));
	return (re);
}


int inside_sphere(t_3d_point point, t_sphere sphere)
{
	float norm;

	norm = pow (point.x - sphere.centre.x, 2)
		+ pow (point.y - sphere.centre.y, 2)
		+ pow (point.z - sphere.centre.z, 2);
	return (norm <= pow (sphere.rayon, 2));
}

t_3d_point reflect(t_3d_point in, t_3d_point normal)
{
    t_3d_point reflection;
    float dotP = dot(in, normal);

    reflection.x = in.x - (2.f * dotP * normal.x);
    reflection.y = in.y - (2.f * dotP * normal.y);
    reflection.z = in.z - (2.f * dotP * normal.z);
    return (reflection);
}


float deg_to_rad(float angle_deg)
{
	return ((angle_deg * M_PI) / (180));
}

t_2d_point spherique_to_iso(t_3d_point a)
{
	t_2d_point	re;
	float		angle_deg;

	float angle_x;
	float angle_y;
	
	angle_deg = 60;

	angle_x = deg_to_rad(angle_deg); 
	angle_y = deg_to_rad(90 - angle_deg); 

	re.x = (a.x * cos(angle_x)) - (a.y * cos(angle_x));
	re.y = (a.x * sin (angle_y)) + (a.y * sin(angle_y)) - a.z;
	return (re);
}

int inside_the_cercle (float x, float y, float rayon)
{
	int dis = (pow (x, 2) + pow (y, 2));
	return (dis <= pow(rayon, 2));
}

t_3d_point iso_to_cart(t_2d_point input)
{
	t_3d_point	re;
	float		angle_deg;

	float angle_x;
	float angle_y;
	
	angle_deg = 60;

	angle_x = deg_to_rad(angle_deg); 
	angle_y = deg_to_rad(90 - angle_deg); 
	re.x = ((input.x / cos (angle_x)) + (input.y / cos(angle_x)) / 2);
	re.y = (input.y - (input.x * tan(angle_y))) / (2 * sin(angle_y));
	re.z = (input.x / cos(angle_x)) + (input.y / cos(angle_x) / 2) - re.y;
	return (re);
}

float delta_equa(float a, float b, float c)
{
	float delta;

	delta = (b * b) - (4 * a * c);
	return (delta);
}


float solution1_equation_2deg(float a, float b , float delta)
{
	return ((-b - sqrtf(delta)) / (2 * a));
}

float solution2_equation_2deg(float a, float b , float delta)
{
	return ((-b + sqrtf(delta)) / (2 * a));
}

float norm_euclidienne_3d(t_3d_point vecteur)
{
	return (sqrtf(pow (vecteur.x, 2) + pow (vecteur.y, 2) + pow (vecteur.z, 2)));
}

float dot(t_3d_point v1, t_3d_point v2)
{
	return (((v1.x * v2.x)  + (v1.y * v2.y) + (v1.z * v2.z)));
}

t_3d_point vecteur_normalise(t_3d_point vecteur)
{
	t_3d_point	re;
	float		norm_euc;

	norm_euc = norm_euclidienne_3d(vecteur);
	re.x = vecteur.x / norm_euc; 
	re.y = vecteur.y / norm_euc; 
	re.z = vecteur.z / norm_euc; 
	return (re);
}

t_3d_point produit_3d_point_par_cst(t_3d_point point, const float cst)
{
	point.x *= cst;
	point.y *= cst;
	point.z *= cst;
	return (point);
}

float length(t_3d_point v)
{
	return (sqrtf(dot(v, v)));
}


float length2d(t_2d_point a)
{
	return sqrt(a.x * a.x + a.y * a.y);
}


int equation_deuxieme_degre(float a, float b, float c, t_intersection *intersection)
{
	float delta = delta_equa(a, b, c);
	if (delta < 0)
		return (0);
	if (delta == 0)
	{
		intersection->x1 = -b / (2 * a);
		intersection->x2 = intersection->x1;
		intersection->min = intersection->x1;
		return (1);
	}
	intersection->x1 = (-b - sqrt(delta)) / (2 * a);
	intersection->x2 = (-b + sqrt(delta)) / (2 * a);
	intersection->min = intersection->x1;
	if (intersection->x2 < intersection->x1)
		intersection->min = intersection->x2;
	return (2);
}

t_3d_point project_to_3d(t_2d_point point_2d)
{
    t_3d_point point_3d;
	float constant_depth = 0;

	point_3d.x = point_2d.x;
    point_3d.y = point_2d.y;
    point_3d.z = constant_depth;

    return (point_3d);
}

// this function make sure you are sill betwen max and min
float clamp (float a, float min, float max)
{
	if (a > max)
		return (max);
	else if (a < min)
		return (min);
	else
		return (a);
}

/************************************/
/************************************/
/************************************/

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

float sphere_phong(t_camera camera, t_light light, t_intersection intersection, float coeff)
{
	float reflect;
	float phong_term;
	t_3d_point phong_dir;
	float specular_value;
	float specular_power;

	specular_value = 0.009f;
	specular_power = 10.f;
	reflect = 2.f * (-dot (light.direction, intersection.normal_vect));
	phong_dir = soustraction_3d_point(light.direction, produit_3d_point_par_cst(intersection.normal_vect, reflect));
	phong_term  = fmax(dot (phong_dir, camera.direction), 0.f);
	phong_term = specular_value * powf (phong_term, specular_power) * coeff;
	return (phong_term);
}

float angle_between(t_3d_point u, t_3d_point v)
{
    float dotProduct = dot(u, v);
    float normu = sqrt(dot(u, u));
    float normv = sqrt(dot(v, v));
    
    float cosTheta = dotProduct / (normu * normv);
    return acos(cosTheta);
}

float the_cylindre(t_3d_point p, t_3d_point a, t_3d_point b, float r)
{
	t_3d_point ba = soustraction_3d_point(b, a);
	t_3d_point pa = soustraction_3d_point(p, a);
	float baba = dot (ba, ba);
	float paba = dot (pa, ba);
	float x = length(soustraction_3d_point(produit_3d_point_par_cst(pa, baba), produit_3d_point_par_cst(ba, paba))) - r * baba;
	float y = fabs(paba - baba * 0.5) - baba * 0.5;
	float x2 = x * x;
	float y2 = y * y * baba;
	float d = (fmax(x,y)<0.0)?-fmin(x2,y2):(((x>0.0)?x2:0.0)+((y>0.0)?y2:0.0));
	float sign = (d > 0)? 1: -1;
	return (sign * sqrtf (fabs (d)) / baba);
}

float sphere(t_3d_point p, float s)
{
  return length(p)-s;
}

float plane(t_3d_point p, t_3d_point n, float h)
{
	return dot(p,n) + h;
}

int min_tab_index(float *tab, int size)
{
	int i;
	int min_index;
	float min;

	min = tab[0];
	i = 0;
	min_index = 0;
	while (i < size)
	{
		if (min > tab[i])
		{
			min = tab[i];
			min_index = i;
		}
		i++;
	}
	return (min_index);
}



float map (t_3d_point pos, t_all *all)
{
	float *re;
	int	  i;
	float cy;
//	float sp;
	float pl;
	float min;

	re = malloc (sizeof (float) * (all->nmb_shape));
	i = 0;
	min = 0;
	while (i < all->nmb_sp)
	{
		re [i] = sphere(soustraction_3d_point(pos, all->sphere[i].centre), all->sphere[i].rayon);
		i++;
	}
	if (all->nmb_sp)
	{
		i = min_tab_index(re, all->nmb_sp);
		min = re[i];
		all->map.color = all->sphere[i].color;
	}
//	min = sphere(soustraction_3d_point(pos, all->sphere[0].centre), all->sphere[0].rayon);
//	pl = sphere(soustraction_3d_point(pos, all->sphere[1].centre), all->sphere[1].rayon);
//	min = fmin (min, pl);
//	if (min == pl)
//		all->map.color = all->sphere[1].color;
//	else
//		all->map.color = all->sphere[0].color;
////////////////////////////////////////
//	i = 0;
//	while (i < all->nmb_cy)
//	{
//		re [i] = the_cylindre(pos, all->cylinder.top, all->cylinder.bottom, all->cylinder.rayon);
//		if (i == 0)
//		{
//			min = re [i];
//			all->map.color = all->cylinder[i].color;
//		}
//		else if (i > 0 && re[i - 1] < re [i])
//		{
//			min = re [i - 1];
//			all->map.color = all->cylinder[i - 1].color;
//		}
//		i++;
//	}
//	i = 0;
//	while (i < all->nmb_cy)
//	{
//		re [i] = the_cylindre(pos, all->cylinder.top, all->cylinder.bottom, all->cylinder.rayon);
//		if (i == 0)
//		{
//			min = re [i];
//			all->map.color = all->cylinder[i].color;
//		}
//		else if (i > 0 && re[i - 1] < re [i])
//		{
//			min = re [i - 1];
//			all->map.color = all->cylinder[i - 1].color;
//		}
//		i++;
//	}


	cy = the_cylindre(pos, all->cylinder.top, all->cylinder.bottom, all->cylinder.rayon);
//	sp = sphere(soustraction_3d_point(pos, all->sphere[i].centre), all->sphere.rayon);
    pl = plane(soustraction_3d_point(pos, all->plan.position), all->plan.normal, 0.f);
//	re = cy;
	min = fmin(min, cy);
	min = fmin(min ,pl);
	if (min == cy)
		all->map.color = all->cylinder.color;
//	else if (re == sp)
//		all->map.color = all->sphere.color;
	if (min == pl)
		all->map.color = all->plan.color;
//	all->map.min = re;
//	return (re);
	free (re);
	return (min);
}

t_3d_point color_multi(t_3d_point a, t_rgb color)
{
	return (vec3(a.x * color.r, a.y * color.b, a.z * color.g));
}

t_3d_point calcul_normal(t_3d_point pos, t_all *all)
{
	t_2d_point e = (t_2d_point){0.5f, -0.5f};
	t_3d_point v1 = vec3 (e.x, e.y, e.y);
	t_3d_point v2 = vec3 (e.y, e.y, e.x);
	t_3d_point v3 = vec3 (e.y, e.x, e.y);
	t_3d_point v4 = vec3 (e.x, e.x, e.x);
	t_3d_point a1 = produit_3d_point_par_cst(v1 , map(somme_3d_point(pos, produit_3d_point_par_cst(v1, EPSILON)), all));
	t_3d_point a2 = produit_3d_point_par_cst(v2 , map(somme_3d_point(pos, produit_3d_point_par_cst(v2, EPSILON)), all));
	t_3d_point a3 = produit_3d_point_par_cst(v3 , map(somme_3d_point(pos, produit_3d_point_par_cst(v3, EPSILON)), all));
	t_3d_point a4 = produit_3d_point_par_cst(v4 , map(somme_3d_point(pos, produit_3d_point_par_cst(v4, EPSILON)), all));
	t_3d_point re = vecteur_normalise(somme_3d_point(somme_3d_point(a1, a2), somme_3d_point(a3, a4)));
	return (re);
}

float calc_shadow(t_3d_point pos, t_all all, float mint, float tmax)
{
	float re;
	float t;
	float s;
	float h;
	int i;

	i = 0;
	re = 1.0;
	t = mint;
	while (i < 25)
	{
		h = map(somme_3d_point(pos,  produit_3d_point_par_cst(all.plan.light.direction, t)), &all);
		s = clamp(10.0 * h / t,0.0,1.0);
		re = fmin(re, s); 
		t += clamp(h, 0.01, 0.2);
		if(re < 0.004 || t > tmax)
			break;
	}
	return (re);
}


float raymarching(t_all *all, t_3d_point direction)
{
	int 		i;
	float		t;
	t_3d_point	pos;
	float 		h;

	i = 0;
	t = 0;
	while (i < ITERATION)
	{
		pos = somme_3d_point(all->camera.direction, produit_3d_point_par_cst(direction, t));
		h = map (pos, all);
		if (t > T_MAX || h < 1e-4)
			break;
		t += h;
		i++;
	}
	return (t);
}

int raytracing_shape(t_all *all, t_3d_point direction)
{
	t_3d_point		color;
	float			t;
	t_3d_point		pos;
	float			diff;
	float			amb; 

	t = raymarching(all, direction);
	if (t <= T_MAX)
	{
		pos = somme_3d_point(all->camera.direction, produit_3d_point_par_cst(direction, t));
		t_3d_point norm = calcul_normal(pos, all);
		diff = clamp(dot (norm, vec3 (0, 1, 0)), 0.f, 1.f);
		diff *= calc_shadow (pos, *all, 0.02, 1.5f);
		amb = (0.5f + 0.5f  * dot (norm, all->plan.light.direction));
		color = produit_3d_point_par_cst(vec3 (amb + diff, amb + diff, amb + diff), all->plan.light.lumnosite);
		color = color_multi(color, all->map.color);
		return (rgb_to_int(color.x, color.y, color.z));
	}
	return (0.f);
}

void draw_shape(t_all *all, t_data *image)
{
	t_3d_point	direction;
	float		half_fov;
	float		pixel_color;
	float		ndc_x;
	float		ndc_y;

	half_fov = tan (deg_to_rad(all->camera.fov / 2.0));
	all->plan.x = 0;
	while (all->plan.x < HEIGHT)
	{
		all->plan.y = 0;
		while (all->plan.y < WIDTH)
		{
			ndc_x = ((2.0f * (all->plan.y + 0.5f) / WIDTH) - 1.0f) * RATIO;
			ndc_y =  1.0f - 2.0f * (all->plan.x + 0.5f) / HEIGHT;
			direction = vec3 (ndc_x * half_fov, ndc_y * half_fov, 5.0f);
			direction = soustraction_3d_point(direction, all->camera.position);
			direction = vecteur_normalise(direction);
			pixel_color = raytracing_shape(all, direction);
			if (pixel_color)
				my_mlx_pixel_put(image , all->plan.y, all->plan.x , pixel_color);
			all->plan.y++;
		}
		all->plan.x++;
	}
}

void stay_a_color(int *color)
{
	if ((*color) > 255)
		(*color) = 255;
	else if ((*color) < 0)
		(*color) = 0;
}

int rgb_to_int(int r, int g, int b) 
{
	int color;

	stay_a_color(&r);
	stay_a_color(&g);
	stay_a_color(&b);
	color = (r << 16) | (g << 8) | b;
	return color;
}

void cylindre_bottom(t_cylinder *cylinder)
{
	cylinder->top = somme_3d_point(cylinder->position, produit_3d_point_par_cst(cylinder->normal, 0.5f * cylinder->hauteur));
	cylinder->bottom = soustraction_3d_point(cylinder->position, produit_3d_point_par_cst(cylinder->normal, 0.5f * cylinder->hauteur));
}

void	free_shapes(t_shapes *shapes)
{
	if (shapes->cylinder)
	{
		free (shapes->cylinder);
		shapes->cylinder = NULL;
	}
	if (shapes->sphere)
	{
		shapes->sphere = NULL;
		free (shapes->sphere);
	}
	if (shapes->plane)
	{
		shapes->plane = NULL;
		free (shapes->plane);
	}
	if (shapes)
		free (shapes);
}

int	escupe_fnct(int keycode, t_shapes *shapes)
{
	if(keycode == 53)
	{
		free_shapes(shapes);
		exit (0);
	}
	return (0);
}

int	red_buttom(t_shapes *shapes)
{
	free_shapes(shapes);
	exit(1);
}

//int moving_light(t_all *all)
//{
//	static float a = 0.01f;
//	a = 0.05f + a;
//
//	printf ("%f \n",a);
//	all->sphere.centre.y += a;
//	draw_shape(all, &all->image);
//	mlx_put_image_to_window(all->mlx.init, all->mlx.win, all->image.img, 0, 0);
//	return (0);
//}

void minirt(t_shapes *shapes)
{
	t_all		all;
	t_mlx		mlx;
	t_plan		plan;
	t_data		image;
	t_sphere	*sphere;
	t_camera	camera;
	t_cylinder	cylinder;
	

	mlx.init = mlx_init();
	mlx.win = mlx_new_window(mlx.init, WIDTH, HEIGHT, "miniRt");
	image.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel , &image.line_length, &image.endian);
	
	/*			PLAN			*/

	plan.z = 1;
	plan.centre_screen_x = HEIGHT / 2.f;
	plan.centre_screen_y = WIDTH / 2.f;
	plan.light.direction = vecteur_normalise(shapes->light.orig);
	plan.light.lumnosite = shapes->light.light_bright;
	//plan.light.position = (t_3d_point){0, 0, 1};


	plan.position = shapes->plane->point;
	plan.normal = shapes->plane->norm_vect;
	plan.color.r = shapes->plane->color.x;
	plan.color.g = shapes->plane->color.z;
	plan.color.b = shapes->plane->color.y;

	/*			CAMERA			*/

	// camera.position.x = 0.7;
	// camera.position.y = 0;
	// camera.position.z = 0;
	camera.position = shapes->camera.orig;
	// camera.direction.x = 0.4;
	// camera.direction.y = 0;
	// camera.direction.z = -1.1f;
	camera.direction = shapes->camera.norm_vect;
	camera.fov = shapes->camera.fov;

	/*			CYLINDER			*/


	cylinder.color = (t_rgb){0, 255, 0};
	cylinder.color.r = shapes->cylinder->color.x;
	cylinder.color.g = shapes->cylinder->color.z;
	cylinder.color.b = shapes->cylinder->color.y;
	cylinder.position = shapes->cylinder->centre;
	cylinder.rayon = shapes->cylinder->diameter / 2;
	cylinder.hauteur = shapes->cylinder->height;
	cylinder.normal = shapes->cylinder->norm_vect;
	cylindre_bottom(&cylinder);
	//point_printer(cylinder.top);
	//point_printer(cylinder.bottom);

	
	
	
	





	/*			LIGHT			*/

//	plan.light.x = 0;
//	plan.light.y = -1000;
//	plan.light.z = 0;

    
	/*		CERCLE INFOS		*/


    // cercle.color = COLOR_B; 
//	cercle.rayon = 300;
//	cercle.centre_x = 0;
//	cercle.centre_y = 0;
//	draw_cercle(mlx, plan, cercle, &image);


	/*	AND WHAT ABOUT SPHERE	*/

//	sphere.color.r = shapes->sphere->color.x; 
//	sphere.color.g = shapes->sphere->color.z; 
//	sphere.color.b = shapes->sphere->color.y; 
//	sphere.centre = shapes->sphere->center;
//	sphere.rayon = shapes->sphere->diameter / 2;

	int i = 0;
	sphere = malloc (sizeof (t_sphere) * shapes->nmb_sp);
	while (i < shapes->nmb_sp)
	{
		sphere[i].color.r = shapes->sphere[i].color.x; 
		sphere[i].color.g = shapes->sphere[i].color.z; 
		sphere[i].color.b = shapes->sphere[i].color.y; 
		sphere[i].centre = shapes->sphere[i].center;
		sphere[i].rayon = shapes->sphere[i].diameter / 2;
		i++;
	}



	all.nmb_sp = shapes->nmb_sp;
	all.nmb_cy = shapes->nmb_cy;
	all.nmb_plan = shapes->nmb_plane;
	all.nmb_shape = shapes->nmb_sp + shapes->nmb_cy + shapes->nmb_plane;

	all.mlx = mlx;
	all.plan = plan;
	all.sphere = sphere;
	all.image = image;
	all.camera = camera;
	all.cylinder = cylinder;





	draw_shape(&all, &image);

 //	 mlx_loop_hook(mlx.init, moving_light, &all);

	/****************************/

	mlx_put_image_to_window(mlx.init, mlx.win, image.img, 0, 0);
	mlx_hook(mlx.win, 2, 0, escupe_fnct, shapes);
	mlx_hook(mlx.win, 17, 0, red_buttom, shapes);
	mlx_loop(mlx.init);
}
