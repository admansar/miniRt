#include "lib_point.h"

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


