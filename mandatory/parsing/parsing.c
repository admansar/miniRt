/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:32:46 by selkhadr          #+#    #+#             */
/*   Updated: 2023/09/02 00:51:48 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_double_array(char **c)
{
	int	i;

	i = 0;
	if (!c)
		return ;
	while (c[i])
	{
		free (c[i]);
		c[i] = NULL;
		i++;
	}
	free (c);
}

void	allocate_shapes(t_shapes *shapes)
{
	shapes->cylinder = ft_calloc(shapes->nmb_cy + 1, sizeof(t_cylinder_info));
	shapes->sphere = ft_calloc(shapes->nmb_sp + 1, sizeof(t_sphere_info));
	shapes->plane = ft_calloc(shapes->nmb_plane + 1, sizeof(t_plane_info));
}

void	calcul_nmb_sequel(t_shapes *shapes, char *all)
{
	char	**str;
	char	**split;
	int		i;

	str = ft_split(all, '\n');
	i = 0;
	while (str[i])
	{
		split = minirt_split(str[i]);
		if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
			shapes->nmb_cy++;
		else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
			shapes->nmb_sp++;
		else if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
			shapes->nmb_plane++;
		free_double_array(split);
		i++;
	}
	free_double_array(str);
	allocate_shapes(shapes);
}

void	calcul_nmbr_of_shapes(char *all, t_shapes *shapes)
{
	char	**split;
	char	**tmp;
	int		i;
	int		a;

	calcul_nmb_sequel(shapes, all);
	shapes->cylinder->nmb = 0;
	shapes->plane->nmb = 0;
	shapes->sphere->nmb = 0;
	tmp = ft_split(all, '\n');
	free (all);
	i = 0;
	while (tmp[i])
	{
		split = minirt_split(tmp[i]);
		shapes_fnct(shapes, split);
		free_double_array(split);
		i++;
	}
	a = shapes->ambient.nmb;
	free_double_array(tmp);
	if (a != 1 || shapes->camera.nmb != 1 || shapes->light.nmb != 1)
		print_error(NULL, NULL, "", shapes);
}

int	main(int ac, char **av)
{
	int				fd;
	t_shapes		*shapes;
	char			*str;

	if (ac != 2 || (ac == 2 && ft_strncmp_dual(av[1], ".rt", 4)))
		return (help());
	shapes = malloc(sizeof(t_shapes));
	init_shape(shapes);
	fd = check_file(av, shapes);
	str = read_from_file(shapes, fd);
	calcul_nmbr_of_shapes(str, shapes);
	minirt(shapes);
	free_shapes(shapes);
	return (0);
}
