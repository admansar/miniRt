#include "../minirt.h"

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
