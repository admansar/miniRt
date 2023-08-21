#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#ifndef WIDTH_HEIGHT
#define WIDTH 1000
#define HEIGHT 1000
#define RATIO (float)WIDTH / HEIGHT
#endif 

#ifndef COLOR_R
#define COLOR_R 255
#endif

#ifndef COLOR_G
#define COLOR_G 0

#endif

#ifndef COLOR_B
#define COLOR_B 0
#endif

#ifndef MIN_LIMITS
#define MIN_LIMITS 1e-6
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

typedef struct s_3d_point
{
	float x;
	float y;
	float z;
}				t_3d_point;

typedef struct s_2d_point
{
	float x;
	float y;
}				t_2d_point;

typedef struct s_rgb
{
	float	r;
	float	b;
	float	g;
}				t_rgb;

typedef struct s_light
{
	t_3d_point	direction;
	//t_3d_point	position; // just added ... not included in the sphere yet
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
	int			in;
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
	int			in;
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
	int			in;
    float		hauteur;     
}				t_cylinder;

typedef struct s_all
{
	t_mlx		mlx;
	t_plan		plan;
	t_cercle	cercle;
	t_data		image;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_camera	camera;
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

int intersect(t_camera camera, t_3d_point direction, t_sphere sphere, t_intersection *intersection)
{
	int num_solutions;
	float a;
	float b;
	float c;
	t_3d_point soust;

	soust = soustraction_3d_point(camera.position, sphere.centre);
	a = norm_euclidienne_3d(direction);
	b = 2.f * dot(direction, soust);
	c = dot(soust, soust) - powf (sphere.rayon, 2.f);
	num_solutions = equation_deuxieme_degre(a, b, c, intersection);
	if (num_solutions)
	{
		//printf ("yes\n");
		intersection->hiting_point.x = camera.position.x + intersection->min * direction.x;
		intersection->hiting_point.y = camera.position.y + intersection->min * direction.y;
		intersection->hiting_point.z = camera.position.z + intersection->min * direction.z;
		intersection->normal_vect = soustraction_3d_point(intersection->hiting_point, sphere.centre);
		return (1);
	}
	intersection->hiting_point = (t_3d_point){0, 0, 0};
	return (0);
}

float sphere_blin_phong(t_camera camera, t_light light, t_intersection intersection, float coeff)
{
	float blin_term;
	t_3d_point blinder;
	float tmp;
	float specular_value;
	float specular_power;

	specular_value = 0.009f;
	specular_power = 10.f;
	blinder = soustraction_3d_point(light.direction, camera.direction);
	tmp = sqrtf(dot (blinder, blinder));
	if (tmp)
	{
		blinder = produit_3d_point_par_cst(blinder, (1.f / tmp));
		blin_term = fmax(dot (blinder, intersection.normal_vect), 0.f);
		blin_term = specular_value * powf(blin_term, specular_power) * coeff;
		return (blin_term);
	}
	return (0.f);
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

int is_shadow(t_plan plan, t_sphere sphere, t_3d_point direction, float *angle)
{
//	float 		t;
//	t_3d_point	intersection;
//	t_3d_point	shadow_centre;
//	float		shadow_rayon;
//	t_cercle	cercle;
//	t_sphere	shadow;

//	t = (dot (plan.normal, soustraction_3d_point(direction, sphere.centre))) / (dot (plan.normal, soustraction_3d_point(plan.light.direction, sphere.centre)));
//	//printf ("%f\n", t);
//	intersection = somme_3d_point(sphere.centre, produit_3d_point_par_cst(soustraction_3d_point(plan.light.direction, sphere.centre), t));
//	shadow_centre = soustraction_3d_point(sphere.centre, produit_3d_point(produit_3d_point(soustraction_3d_point(sphere.centre, direction), plan.normal), plan.normal));
//	shadow_rayon = distance_3d_point(intersection, shadow_centre);
	*angle  = angle_between (plan.light.direction, direction);
	//printf ("%f \n", angle);
	if (!(*angle >= M_PI / 4  && *angle <= M_PI))
	{
		return (1);
	}
		//if ((int)t == 0)
	//	return (1);
//	if (inside_the_cercle(direction.x, direction.y, shadow_rayon))
//		return (1);
	//point_printer(shadow_centre);
	return (0);
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

float map (t_3d_point pos, t_all *all)
{
	float re;

	all->plan.in = 0;
	all->sphere.in = 0;
	all->cylinder.in = 0;
	float cy = the_cylindre(pos, all->cylinder.top, all->cylinder.bottom, all->cylinder.rayon);
	float sp = sphere(soustraction_3d_point(pos, all->sphere.centre), all->sphere.rayon);
    float pl = plane(soustraction_3d_point(pos, all->plan.position), all->plan.normal, 0.f);
	re = cy;
	re = fmin(re, sp);
	re = fmin(re ,pl);
	if (re == pl)
		all->plan.in = 1;
	else if (re == cy)
		all->cylinder.in = 1;
	else if (re == sp)
		all->sphere.in = 1;
	//printf ("IN %d %d %d \n", all->plan.in, all->cylinder.in, all->sphere.in);
	return (re);
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
	t_3d_point a1= produit_3d_point_par_cst(v1 , map(somme_3d_point(pos, produit_3d_point_par_cst(v1, EPSILON)), all));
	t_3d_point a2= produit_3d_point_par_cst(v2 , map(somme_3d_point(pos, produit_3d_point_par_cst(v2, EPSILON)), all));
	t_3d_point a3= produit_3d_point_par_cst(v3 , map(somme_3d_point(pos, produit_3d_point_par_cst(v3, EPSILON)), all));
	t_3d_point a4= produit_3d_point_par_cst(v4 , map(somme_3d_point(pos, produit_3d_point_par_cst(v4, EPSILON)), all));
	t_3d_point re = vecteur_normalise(somme_3d_point(somme_3d_point(a1, a2), somme_3d_point(a3, a4)));
	return (re);
}




int raytracing_shape(t_all *all, t_3d_point direction)
{
	t_3d_point		color;
	float			t;
	t_3d_point		pos;
	float			h;
	float			diff;
	float			amb; 
	int				i;

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
	color = vec3(0,0,0);
	if (t <= T_MAX)
	{
		pos = somme_3d_point(all->camera.direction, produit_3d_point_par_cst(direction, t));
		t_3d_point norm = calcul_normal(pos, all);
		diff = clamp(dot (norm, vec3 (0, 1, 0)), 0.f, 1.f);
		amb = 0.5f + 0.5f  * dot (norm, all->plan.light.direction);
		t_3d_point vect = vec3(1, 1, 1);
		color = somme_3d_point(produit_3d_point_par_cst(vect, amb), produit_3d_point_par_cst(vect, diff));
		color = vec3(sqrtf(color.x), sqrtf(color.y), sqrtf(color.z));
		if (all->cylinder.in == 1)
		color = color_multi(color, all->cylinder.color); 
		else if (all->sphere.in == 1)
		color = color_multi(color, all->sphere.color); 
		else if (all->plan.in == 1)
		color = color_multi(color, all->plan.color); 
		//printf ("OUT %d %d %d \n", all->plan.in, all->cylinder.in, all->sphere.in);
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
			direction = vec3 (ndc_x * half_fov, ndc_y * half_fov, 1.f);
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
float raytracing(t_camera camera, t_3d_point direction, t_sphere sphere, t_plan plan)
{
	t_intersection	intersection;
	t_3d_point		re;
	float			coeff;
	float			in;
	t_3d_point		specular;
	t_3d_point		blin_phong;
	float			lumnosite;
	float			tmp;
	float			color;
	float			facteur;
	float			angle;

	re = vec3(0,0,0);
	if (intersect(camera, direction, sphere, &intersection))
	{
		lumnosite = 1 / sphere.rayon;
		coeff = -dot (plan.light.direction, intersection.normal_vect);
		//printf ("--%f\n", coeff);
		in = coeff * (lumnosite);
		re = vec3(in * sphere.color.r, in * sphere.color.g , in * sphere.color.b);
		tmp = sphere_phong(camera, plan.light, intersection, coeff);
		specular = vec3(tmp * (float)sphere.color.r, tmp * (float)sphere.color.g, tmp * (float)sphere.color.b);
		tmp = sphere_blin_phong(camera, plan.light, intersection, coeff);
		blin_phong = vec3(tmp * (float)sphere.color.r, tmp * (float)sphere.color.g, tmp * (float)sphere.color.b);
		color = rgb_to_int(re.x + specular.x + blin_phong.x,re.y + specular.y + blin_phong.y,re.z + specular.z + blin_phong.z);
		if (color == 0)
			return (1.f);
		return (color);
	}
	if (intersectplan(plan, camera, direction))
	{
		//coeff = 0.7f * (-dot (direction, plan.light.direction));
		coeff = 0;
		//printf ("-%f\n", coeff / 0.7f);
		facteur = 1.f * dot (direction, camera.direction);
		//facteur = 0;
		if (is_shadow(plan, sphere, direction, &angle))
		{
			if (angle >= 0.f && angle <= 0.2f)
				return (1.f);
		}
		return (rgb_to_int((coeff + facteur) * (float)plan.color.r, (coeff + facteur) * (float)plan.color.g, (coeff + facteur) * (float)plan.color.b));
	}
	return (0.f);
}

void draw_sphere(t_mlx mlx, t_plan plan, t_sphere sphere, t_data *image, t_camera camera)
{
	t_3d_point	direction;
	float		half_fov;
	float		ratio;
	float		pixel_color;
	int			x;
	int			y;
	float		ndc_x;
	float		ndc_y;

	ratio = RATIO;
	half_fov = tan (deg_to_rad(camera.fov / 2.0));
	plan.x = 0;
	while (plan.x < HEIGHT)
	{
		plan.y = 0;
		while (plan.y < WIDTH)
		{
			//point.x = (plan.x - plan.centre_screen_x) / 1088.f;
			//point.y = (plan.y - plan.centre_screen_y) / 1088.f;
			//input = project_to_3d(point);
		//	if (inside_sphere(input, sphere))
			{
				x = plan.y;
				y = plan.x;
				ndc_x = ((2.0f * (x + 0.5f) / WIDTH) - 1.0f) * ratio;
				ndc_y =  1.0f - 2.0f * (y + 0.5f) / HEIGHT;
				direction.x = ndc_x * half_fov;
				direction.y = ndc_y * half_fov;
				direction.z = 1.0;
				direction = soustraction_3d_point(direction, camera.position);
				direction = vecteur_normalise(direction);
				pixel_color = raytracing(camera, direction, sphere, plan);
				if (pixel_color)
					my_mlx_pixel_put(image , x, y , pixel_color);
			}
			plan.y++;
		}
		plan.x++;
	}
}

void draw_cercle(t_mlx mlx, t_plan plan, t_cercle cercle, t_data *image)
{
	plan.x = -plan.centre_screen_x + 1;
	while (plan.x < plan.centre_screen_x)
	{
		plan.y = -plan.centre_screen_y + 1;
		while (plan.y < plan.centre_screen_y)
		{
			if (inside_the_cercle(plan.x, plan.y, cercle.rayon))
			{
				my_mlx_pixel_put(image , WIDTH/2 + plan.x + cercle.centre_x, HEIGHT/2 - plan.y - cercle.centre_y , cercle.color);
			}
			plan.y++;
		}
		plan.x++;
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
	//printf (" %d %d %d\n", r, g, b);
	color = (r << 16) | (g << 8) | b;
	return color;
}


void draw_color(t_mlx mlx, t_rgb rgb, t_data *image)
{
	int i;
	int j;
	int color;

	i = 1;
	rgb.r = 0;
	rgb.g = 101;
	rgb.b = 255;
	while (i < WIDTH)
	{
		j = 1;
		while (j < HEIGHT)
		{
			my_mlx_pixel_put(image, i, j, rgb_to_int(rgb.r, rgb.g, rgb.b));
			j++;
		}
		i++;
	}
}


void cylindre_bottom(t_cylinder *cylinder)
{
	cylinder->top = somme_3d_point(cylinder->position, produit_3d_point_par_cst(cylinder->normal, 0.5f * cylinder->hauteur));
	cylinder->bottom = soustraction_3d_point(cylinder->position, produit_3d_point_par_cst(cylinder->normal, 0.5f * cylinder->hauteur));
}


int moving_light(t_all *all)
{
	static float a = 0.01f;
	t_3d_point vect;
	a = 0.05f + a;
	
	vect = vec3 (0.f + a,-1.f + a, -0.2);
	all->plan.light.direction = vecteur_normalise(vect);
	//printf ("%f\n", a);
	//point_printer(vect);
//	all->cylinder.normal = (t_3d_point){0.f - a,0.f,0.f + a};
//	cylindre_bottom(&all->cylinder);
	mlx_clear_window(all->mlx.init, all->mlx.win);
	//draw_shape(all->mlx, all->plan, all->cylinder, &all->image, all->camera);
//	draw_sphere(all->mlx, all->plan, all->sphere[0], &all->image, all->camera);
//	draw_sphere(all->mlx, all->plan, all->sphere[1], &all->image, all->camera);
//	draw_sphere(all->mlx, all->plan, all->sphere[2], &all->image, all->camera);
	
	mlx_put_image_to_window(all->mlx.init, all->mlx.win, all->image.img, 0, 0);
	return (0);
}

int intersectplan(t_plan plan, t_camera camera, t_3d_point direction)
{
	float domen = dot(plan.normal, direction);
	if (fabs(domen) > MIN_LIMITS)
	{
		float t = dot (soustraction_3d_point(plan.position, camera.position), plan.normal) / domen;
		return (t >= 0);
	}
	return (0);
//	printf ("%d\n", t);
//	int t = dot(soustraction_3d_point(direction, plan.position), plan.normal);
//	return (t == 0);
}



int main()
{
	t_all		all;
	t_mlx		mlx;
	t_plan		plan;
	t_cercle	cercle;
	t_data		image;
	t_sphere	sphere;
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
	plan.light.direction = vecteur_normalise(vec3(1.0, 0.0, 1.f));
	plan.light.ambient = 0.8;
	//plan.light.position = (t_3d_point){0, 0, 1};


	plan.position = vec3(0.f, -0.4, 0.f);
	plan.normal = vec3(0.f, 1.f, 0.f);
	plan.color = (t_rgb){0,0,255};
	plan.in = 0;

	/*			CAMERA			*/

	camera.position.x = -0.1;
	camera.position.y = 0;
	camera.position.z = 0;
	camera.direction.x = 0;
	camera.direction.y = 0;
	camera.direction.z = -1.1f;
	camera.fov = 100;

	/*			CYLINDER			*/


	cylinder.color = (t_rgb){0, 255, 0};
	cylinder.position = (t_3d_point){0, 0, 0};
	cylinder.rayon = 0.3f;
	cylinder.hauteur = 1;
	cylinder.in = 0;
	cylinder.normal = (t_3d_point){0.8, 0.2, 1};
	cylindre_bottom(&cylinder);
	//point_printer(cylinder.top);
	//point_printer(cylinder.bottom);

	
	
	
	





	/*			LIGHT			*/

//	plan.light.x = 0;
//	plan.light.y = -1000;
//	plan.light.z = 0;

    
	/*		CERCLE INFOS		*/


    cercle.color = COLOR_B; 
	cercle.rayon = 300;
	cercle.centre_x = 0;
	cercle.centre_y = 0;
//	draw_cercle(mlx, plan, cercle, &image);


	/*	AND WHAT ABOUT SPHERE	*/

	sphere.color.r = COLOR_R; 
	sphere.color.g = COLOR_G; 
	sphere.color.b = COLOR_B; 
	sphere.centre.x = 0.f;
	sphere.centre.y = 0.3f;
	sphere.centre.z = 0.f;
	sphere.rayon = 0.4f;
	sphere.in = 0;







	all.mlx = mlx;
	all.plan = plan;
	all.cercle = cercle;
	all.sphere = sphere;
	all.image = image;
	all.camera = camera;
	all.cylinder = cylinder;






	
	draw_shape(&all, &image);


//	draw_color(mlx, sphere.color, &image);
	//draw_plane(mlx, plan, camera, &image);
//	draw_sphere_shadow(mlx, plan, sphere, camera, &image);
//	sphere.centre.x = 0.0f;
//	sphere.centre.y = 0.0f;
//	sphere.centre.z = 0.0f;
//	sphere.rayon = 0.2f;
//	sphere.color.g = 255; 
//	sphere.color.b = 0;
//	sphere.color.r = 0;
//	all.sphere[1] = sphere;
//	draw_sphere(mlx, plan, sphere, &image, camera);
//	sphere.centre.x = -0.4f;
//	sphere.centre.y = -0.4f;
//	sphere.centre.z = -0.4f;
//	sphere.rayon = 0.1f;
//	sphere.color.g = 0;
//	sphere.color.b = 255;
//	sphere.color.r = 0;
//	draw_sphere(mlx, plan, sphere, &image, camera);
	/*	EVERYTHING IN ONE STRUCT	*/

//	all.sphere[2] = sphere;

		/*		moving time		*/
 //	 mlx_loop_hook(mlx.init, moving_light, &all);

	/****************************/

	mlx_put_image_to_window(mlx.init, mlx.win, image.img, 0, 0);
	mlx_loop(mlx.init);
}
