/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:38:24 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 19:42:52 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_shapes(t_shapes *shapes, t_all *all)
{
	all->nmb_sp = shapes->nmb_sp;
	all->nmb_cy = shapes->nmb_cy;
	all->nmb_plan = shapes->nmb_plane;
	all->nmb_shape = shapes->nmb_sp + shapes->nmb_cy + shapes->nmb_plane;
	all->plan = init_plan(shapes);
	all->sphere = init_sphere(shapes);
	all->camera = init_camera(shapes);
	all->cylinder = init_cylinder(shapes);
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
