/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:46 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:57 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
