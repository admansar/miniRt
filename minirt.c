#include "minirt.h"
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float		dot(t_3d_point v1, t_3d_point v2);
int			inside_the_cercle(float x, float y, float rayon);
int			inside_sphere(t_3d_point point, t_sphere sphere);
int			intersectplan(t_plan plan, t_camera camera, t_3d_point point);
int			rgb_to_int(int r, int g, int b);
/************************************/
/*		OPERATION FOR 3D POINTS		*/
/************************************/

t_3d_point	somme_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point	re;

	re.x = a.x + b.x;
	re.y = a.y + b.y;
	re.z = a.z + b.z;
	return (re);
}

t_3d_point	produit_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point	re;

	re.x = a.x * b.x;
	re.y = a.y * b.y;
	re.z = a.z * b.z;
	return (re);
}

t_3d_point	vec3(float x, float y, float z)
{
	t_3d_point	re;

	re.x = x;
	re.y = y;
	re.z = z;
	return (re);
}

t_3d_point	cross(t_3d_point a, t_3d_point b)
{
	return (vec3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x
				* b.y) - (a.y * b.x)));
}

void	point_printer(t_3d_point a)
{
	printf("(%.1f, %.1f, %.1f)", a.x, a.y, a.z);
}

t_3d_point	soustraction_3d_point(t_3d_point a, t_3d_point b)
{
	t_3d_point	re;

	re.x = a.x - b.x;
	re.y = a.y - b.y;
	re.z = a.z - b.z;
	return (re);
}

float	distance_3d_point(t_3d_point a, t_3d_point b)
{
	float	re;

	re = sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (re);
}

float	norm_carre_3d_point(t_3d_point a, t_3d_point b)
{
	float	re;

	re = (pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
	return (re);
}

int	inside_sphere(t_3d_point point, t_sphere sphere)
{
	float	norm;

	norm = pow(point.x - sphere.centre.x, 2) + pow(point.y - sphere.centre.y, 2)
		+ pow(point.z - sphere.centre.z, 2);
	return (norm <= pow(sphere.rayon, 2));
}

t_3d_point	reflect(t_3d_point in, t_3d_point normal)
{
	t_3d_point	reflection;
	float		dotp;

	dotp = dot(in, normal);
	reflection.x = in.x - (2.f * dotp * normal.x);
	reflection.y = in.y - (2.f * dotp * normal.y);
	reflection.z = in.z - (2.f * dotp * normal.z);
	return (reflection);
}

float	deg_to_rad(float angle_deg)
{
	return ((angle_deg * M_PI) / (180));
}

t_2d_point	spherique_to_iso(t_3d_point a)
{
	t_2d_point	re;
	float		angle_deg;
	float		angle_x;
	float		angle_y;

	angle_deg = 60;
	angle_x = deg_to_rad(angle_deg);
	angle_y = deg_to_rad(90 - angle_deg);
	re.x = (a.x * cos(angle_x)) - (a.y * cos(angle_x));
	re.y = (a.x * sin(angle_y)) + (a.y * sin(angle_y)) - a.z;
	return (re);
}

int	inside_the_cercle(float x, float y, float rayon)
{
	int	dis;

	dis = (pow(x, 2) + pow(y, 2));
	return (dis <= pow(rayon, 2));
}

t_3d_point	iso_to_cart(t_2d_point input)
{
	t_3d_point	re;
	float		angle_deg;
	float		angle_x;
	float		angle_y;

	angle_deg = 60;
	angle_x = deg_to_rad(angle_deg);
	angle_y = deg_to_rad(90 - angle_deg);
	re.x = ((input.x / cos(angle_x)) + (input.y / cos(angle_x)) / 2);
	re.y = (input.y - (input.x * tan(angle_y))) / (2 * sin(angle_y));
	re.z = (input.x / cos(angle_x)) + (input.y / cos(angle_x) / 2) - re.y;
	return (re);
}

float	norm_euclidienne_3d(t_3d_point vecteur)
{
	float	re;

	re = powf(vecteur.x, 2) + powf(vecteur.y, 2) + powf(vecteur.z, 2);
	return (sqrtf(re));
}

float	dot(t_3d_point v1, t_3d_point v2)
{
	return (((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z)));
}

t_3d_point	vecteur_normalise(t_3d_point vecteur)
{
	t_3d_point	re;
	float		norm_euc;

	norm_euc = norm_euclidienne_3d(vecteur);
	re.x = vecteur.x / norm_euc;
	re.y = vecteur.y / norm_euc;
	re.z = vecteur.z / norm_euc;
	return (re);
}

t_3d_point	produit_3d_point_par_cst(t_3d_point point, const float cst)
{
	point.x *= cst;
	point.y *= cst;
	point.z *= cst;
	return (point);
}

float	length(t_3d_point v)
{
	return (sqrtf(dot(v, v)));
}

float	length2d(t_2d_point a)
{
	return (sqrt(a.x * a.x + a.y * a.y));
}

t_3d_point	project_to_3d(t_2d_point point_2d)
{
	t_3d_point	point_3d;
	float		constant_depth;

	constant_depth = 0;
	point_3d.x = point_2d.x;
	point_3d.y = point_2d.y;
	point_3d.z = constant_depth;
	return (point_3d);
}

// this function make sure you are sill betwen max and min
float	clamp(float a, float min, float max)
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	angle_between(t_3d_point u, t_3d_point v)
{
	float	dotproduct;
	float	normu;
	float	normv;
	float	costheta;

	dotproduct = dot(u, v);
	normu = sqrt(dot(u, u));
	normv = sqrt(dot(v, v));
	costheta = dotproduct / (normu * normv);
	return (acos(costheta));
}

float	get_cy_dist(t_define_cylindre *cylinder)
{
	float	re;

	if (fmax(cylinder->x, cylinder->y) < 0.f)
		re = -fmin(cylinder->x2, cylinder->y2);
	else
	{
		if (cylinder->x > 0.f)
			re = cylinder->x2;
		else
			re = 0.f;
		if (cylinder->y > 0.0)
			re += cylinder->y2;
	}
	return (re);
}

float	the_cylindre(t_3d_point p, t_3d_point a, t_3d_point b, float r)
{
	t_define_cylindre	cylinder;

	cylinder.ba = soustraction_3d_point(b, a);
	cylinder.pa = soustraction_3d_point(p, a);
	cylinder.baba = dot(cylinder.ba, cylinder.ba);
	cylinder.paba = dot(cylinder.pa, cylinder.ba);
	cylinder.x = length(soustraction_3d_point
			(produit_3d_point_par_cst(cylinder.pa,
					cylinder.baba), produit_3d_point_par_cst(cylinder.ba,
					cylinder.paba))) - r * cylinder.baba;
	cylinder.y = fabs(cylinder.paba - cylinder.baba * 0.5) - cylinder.baba
		* 0.5;
	cylinder.x2 = cylinder.x * cylinder.x;
	cylinder.y2 = cylinder.y * cylinder.y * cylinder.baba;
	cylinder.d = get_cy_dist(&cylinder);
	if (cylinder.d > 0)
		cylinder.sign = 1;
	else
		cylinder.sign = -1;
	return (cylinder.sign * sqrtf(fabs(cylinder.d)) / cylinder.baba);
}

float	sphere(t_3d_point p, float s)
{
	return (length(p) - s);
}

float	plane(t_3d_point p, t_3d_point n, float h)
{
	return (dot(p, n) + h);
}

float	sdcapsule(t_3d_point p, t_3d_point a, t_3d_point b, float r)
{
	t_3d_point	pa;
	t_3d_point	ba;
	float		h;

	pa = soustraction_3d_point(p, a);
	ba = soustraction_3d_point(b, a);
	h = clamp(dot(pa, ba) / dot(ba, ba), 0.0, 1.0);
	return (length(soustraction_3d_point(pa, produit_3d_point_par_cst(ba, h)))
		- r);
}

int	min_tab_index(float *tab, int size)
{
	int		i;
	int		min_index;
	float	min;

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

void	checking_shape(t_3d_point pos, t_all *all, int i, float *re)
{
	if (i < all->holder[0])
		re[i] = sphere(soustraction_3d_point(pos, all->sphere[i].centre),
				all->sphere[i].rayon);
	else if (i < all->holder[1])
		re[i] = the_cylindre(pos, all->cylinder[i - all->holder[0]].top,
				all->cylinder[i - all->holder[0]].bottom, all->cylinder[i
				- all->holder[0]].rayon);
	else if (i < all->holder[2])
		re[i] = plane(soustraction_3d_point(pos, all->plan[i
					- all->holder[1]].position), all->plan[i
				- all->holder[1]].normal, 0.f);
	else
		re[i] = sdcapsule(pos, all->capsule[i - all->holder[2]].top,
				all->capsule[i - all->holder[2]].bottom, all->capsule[i
				- all->holder[2]].rayon);
}

float	map(t_3d_point pos, t_all *all)
{
	float	*re;
	int		i;
	float	min;

	re = malloc(sizeof(float) * (all->nmb_shape));
	min = T_MAX;
	i = -1;
	while (++i < all->nmb_shape)
		checking_shape(pos, all, i, re);
	i = min_tab_index(re, all->nmb_shape);
	min = re[i];
	if (i < all->nmb_sp)
		all->map.color = all->sphere[i].color;
	else if (i < all->nmb_sp + all->nmb_cy && i >= all->nmb_sp)
		all->map.color = all->cylinder[i - all->holder[0]].color;
	else if (i >= all->nmb_sp + all->nmb_cy && i < all->nmb_sp + all->nmb_cy
		+ all->nmb_plan)
		all->map.color = all->plan[i - all->holder[1]].color;
	else
		all->map.color = all->capsule[i - all->holder[2]].color;
	free(re);
	return (min);
}

t_3d_point	color_multi(t_3d_point a, t_rgb color)
{
	return (vec3(a.x * color.r, a.y * color.b, a.z * color.g));
}

t_3d_point	calcul_normal(t_3d_point pos, t_all *all)
{
	t_normal_info	normal;

	normal.e.x = 0.5f;
	normal.e.y = -0.5f;
	normal.v1 = vec3(normal.e.x, normal.e.y, normal.e.y);
	normal.v2 = vec3(normal.e.y, normal.e.y, normal.e.x);
	normal.v3 = vec3(normal.e.y, normal.e.x, normal.e.y);
	normal.v4 = vec3(normal.e.x, normal.e.x, normal.e.x);
	normal.a1 = produit_3d_point_par_cst(normal.v1, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v1, EPSILON)), all));
	normal.a2 = produit_3d_point_par_cst(normal.v2, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v2, EPSILON)), all));
	normal.a3 = produit_3d_point_par_cst(normal.v3, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v3, EPSILON)), all));
	normal.a4 = produit_3d_point_par_cst(normal.v4, map(somme_3d_point(pos,
					produit_3d_point_par_cst(normal.v4, EPSILON)), all));
	normal.re = vecteur_normalise(somme_3d_point(somme_3d_point(normal.a1,
					normal.a2), somme_3d_point(normal.a3, normal.a4)));
	return (normal.re);
}

float	calc_shadow(t_3d_point pos, t_all all, float mint, float tmax)
{
	float	re;
	float	t;
	float	s;
	float	h;
	int		i;

	i = 0;
	re = 1.0;
	t = mint;
	while (i < 25)
	{
		h = map(somme_3d_point(pos,
					produit_3d_point_par_cst(all.plan->light.direction, t)),
				&all);
		s = clamp(10.0 * h / t, 0.0, 1.0);
		re = fmin(re, s);
		t += clamp(h, 0.01, 0.2);
		if (re < 0.004 || t > tmax)
			break ;
	}
	return (re);
}

float	raymarching(t_all *all, t_3d_point direction)
{
	int			i;
	float		t;
	t_3d_point	pos;
	float		h;

	i = 0;
	t = 0;
	while (i < ITERATION)
	{
		pos = somme_3d_point(all->camera.direction,
				produit_3d_point_par_cst(direction, t));
		h = map(pos, all);
		if (t > T_MAX || h < 1e-4)
			break ;
		t += h;
		i++;
	}
	return (t);
}

// diff[1] is the ambient and diff[2] is the specular

int	raytracing_shape(t_all *all, t_3d_point direction)
{
	t_3d_point	color;
	float		t;
	t_3d_point	pos;
	float		diff[3];
	t_3d_point	norm;

	t = raymarching(all, direction);
	if (t <= T_MAX)
	{
		pos = somme_3d_point(all->camera.direction,
				produit_3d_point_par_cst(direction, t));
		norm = calcul_normal(pos, all);
		diff[0] = clamp(dot(norm, vec3(0, 1, 0)), 0.f, 1.f);
		diff[0] *= calc_shadow(pos, *all, 0.02, 1.5f);
		diff[1] = (0.5f + 0.5f * dot(norm, all->plan->light.direction));
		diff[2] = powf(clamp(dot(norm, vecteur_normalise
						(soustraction_3d_point(all->plan->light.direction,
								direction))), 0.0, 1.3), 16.0);
		color = produit_3d_point_par_cst(vec3(diff[1] + diff[0] + diff[2],
					diff[1] + diff[0] + diff[2], diff[1] + diff[0] + diff[2]),
				all->plan->light.lumnosite);
		color = color_multi(color, all->map.color);
		return (rgb_to_int(color.x, color.y, color.z));
	}
	return (0.f);
}

void	draw_shape(t_all *all, t_data *image)
{
	t_3d_point	direction;
	float		half_fov;
	float		pixel_col;
	float		ndc_x;
	float		ndc_y;

	half_fov = tan(deg_to_rad(all->camera.fov / 2.0));
	all->plan->x = 0;
	while (all->plan->x < HEIGHT)
	{
		all->plan->y = 0;
		while (all->plan->y < WIDTH)
		{
			ndc_x = ((2.0f * (all->plan->y + 0.5f) / WIDTH) - 1.0f) * RATIO;
			ndc_y = 1.0f - 2.0f * (all->plan->x + 0.5f) / HEIGHT;
			direction = vec3(ndc_x * half_fov, ndc_y * half_fov, 5.f);
			direction = soustraction_3d_point(direction, all->camera.position);
			direction = vecteur_normalise(direction);
			pixel_col = raytracing_shape(all, direction);
			if (pixel_col)
				my_mlx_pixel_put(image, all->plan->y, all->plan->x, pixel_col);
			all->plan->y++;
		}
		all->plan->x++;
	}
}

void	stay_a_color(int *color)
{
	if ((*color) > 255)
		(*color) = 255;
	else if ((*color) < 0)
		(*color) = 0;
}

int	rgb_to_int(int r, int g, int b)
{
	int	color;

	stay_a_color(&r);
	stay_a_color(&g);
	stay_a_color(&b);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	cylindre_bottom(t_cylinder *cylinder)
{
	cylinder->top = somme_3d_point(cylinder->position,
			produit_3d_point_par_cst(cylinder->normal, 0.5f
				* cylinder->hauteur));
	cylinder->bottom = soustraction_3d_point(cylinder->position,
			produit_3d_point_par_cst(cylinder->normal, 0.5f
				* cylinder->hauteur));
}

void	free_shapes(t_shapes *shapes)
{
	if (shapes->cylinder)
	{
		free(shapes->cylinder);
		shapes->cylinder = NULL;
	}
	if (shapes->sphere)
	{
		shapes->sphere = NULL;
		free(shapes->sphere);
	}
	if (shapes->plane)
	{
		shapes->plane = NULL;
		free(shapes->plane);
	}
	if (shapes)
		free(shapes);
}

void	free_all(t_all *all)
{
	free(all->cylinder);
	free(all->capsule);
	free(all->sphere);
	free(all->plan);
}

int	escupe_fnct(int keycode, t_shapes *shapes)
{
	if (keycode == 53)
	{
		free_all(shapes->all);
		free_shapes(shapes);
		exit(0);
	}
	return (0);
}

int	red_buttom(t_shapes *shapes)
{
	free_all(shapes->all);
	free_shapes(shapes);
	exit(1);
}

t_sphere	*init_sphere(t_shapes *shapes)
{
	int			i;
	t_sphere	*sphere;

	i = 0;
	sphere = malloc(sizeof(t_sphere) * shapes->nmb_sp);
	while (i < shapes->nmb_sp)
	{
		sphere[i].color.r = shapes->sphere[i].color.x;
		sphere[i].color.g = shapes->sphere[i].color.z;
		sphere[i].color.b = shapes->sphere[i].color.y;
		sphere[i].centre = shapes->sphere[i].center;
		sphere[i].rayon = shapes->sphere[i].diameter / 2;
		i++;
	}
	return (sphere);
}

t_plan	*init_plan(t_shapes *shapes)
{
	int		i;
	t_plan	*plan;

	plan = malloc(sizeof(t_plan) * shapes->nmb_plane);
	i = 0;
	while (i < shapes->nmb_plane)
	{
		plan[i].z = 1;
		plan[i].light.direction = vecteur_normalise(shapes->light.orig);
		plan[i].light.lumnosite = shapes->light.light_bright;
		plan[i].centre_screen_x = HEIGHT / 2.f;
		plan[i].centre_screen_y = WIDTH / 2.f;
		plan[i].position = shapes->plane[i].point;
		plan[i].normal = shapes->plane[i].norm_vect;
		plan[i].color.r = shapes->plane[i].color.x;
		plan[i].color.g = shapes->plane[i].color.z;
		plan[i].color.b = shapes->plane[i].color.y;
		i++;
	}
	return (plan);
}

t_cylinder	*init_cylinder(t_shapes *shapes)
{
	t_cylinder	*cylinder;
	int			i;

	cylinder = malloc(sizeof(t_cylinder) * shapes->nmb_cy);
	i = 0;
	while (i < shapes->nmb_cy)
	{
		cylinder[i].color.r = shapes->cylinder[i].color.x;
		cylinder[i].color.g = shapes->cylinder[i].color.z;
		cylinder[i].color.b = shapes->cylinder[i].color.y;
		cylinder[i].position = shapes->cylinder[i].centre;
		cylinder[i].rayon = shapes->cylinder[i].diameter / 2;
		cylinder[i].hauteur = shapes->cylinder[i].height;
		cylinder[i].normal = shapes->cylinder[i].norm_vect;
		cylindre_bottom(&cylinder[i]);
		i++;
	}
	return (cylinder);
}

t_camera	init_camera(t_shapes *shapes)
{
	t_camera	camera;

	camera.position = shapes->camera.orig;
	camera.direction = shapes->camera.norm_vect;
	camera.fov = shapes->camera.fov;
	return (camera);
}

t_capsule	*init_capsule(t_shapes *shapes)
{
	int			i;
	t_capsule	*capsule;

	capsule = malloc(sizeof(t_capsule) * shapes->nmb_capsule);
	i = 0;
	while (i < shapes->nmb_capsule)
	{
		capsule[i].color.r = shapes->capsule[i].color.x;
		capsule[i].color.g = shapes->capsule[i].color.z;
		capsule[i].color.b = shapes->capsule[i].color.y;
		capsule[i].top = shapes->capsule[i].top;
		capsule[i].bottom = shapes->capsule[i].bottom;
		capsule[i].rayon = shapes->capsule[i].diameter / 2;
		i++;
	}
	return (capsule);
}

void	init_shapes(t_shapes *shapes, t_all *all)
{
	all->nmb_sp = shapes->nmb_sp;
	all->nmb_cy = shapes->nmb_cy;
	all->nmb_plan = shapes->nmb_plane;
	all->nmb_capsule = shapes->nmb_capsule;
	all->nmb_shape = shapes->nmb_sp + shapes->nmb_cy + shapes->nmb_plane
		+ shapes->nmb_capsule;
	all->plan = init_plan(shapes);
	all->sphere = init_sphere(shapes);
	all->camera = init_camera(shapes);
	all->cylinder = init_cylinder(shapes);
	all->capsule = init_capsule(shapes);
	all->holder[0] = all->nmb_sp;
	all->holder[1] = all->nmb_cy + all->nmb_sp;
	all->holder[2] = all->nmb_cy + all->nmb_sp + all->nmb_plan;
}

void	minirt(t_shapes *shapes)
{
	t_all	all;
	t_mlx	mlx;
	t_data	image;

	mlx.init = mlx_init();
	mlx.win = mlx_new_window(mlx.init, WIDTH, HEIGHT, "miniRt");
	image.img = mlx_new_image(mlx.init, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	init_shapes(shapes, &all);
	all.mlx = mlx;
	all.image = image;
	draw_shape(&all, &image);
	shapes->all = &all;
	mlx_put_image_to_window(mlx.init, mlx.win, image.img, 0, 0);
	mlx_hook(mlx.win, 2, 0, escupe_fnct, shapes);
	mlx_hook(mlx.win, 17, 0, red_buttom, shapes);
	mlx_loop(mlx.init);
}
