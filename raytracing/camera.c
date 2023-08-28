#include "../minirt.h"

t_camera	init_camera(t_shapes *shapes)
{
	t_camera	camera;

	camera.position = shapes->camera.orig;
	camera.direction = shapes->camera.norm_vect;
	camera.fov = shapes->camera.fov;
	return (camera);
}
