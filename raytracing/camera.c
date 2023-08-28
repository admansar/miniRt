/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:33 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:56 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_camera	init_camera(t_shapes *shapes)
{
	t_camera	camera;

	camera.position = shapes->camera.orig;
	camera.direction = shapes->camera.norm_vect;
	camera.fov = shapes->camera.fov;
	return (camera);
}
