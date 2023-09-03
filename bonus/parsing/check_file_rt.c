/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_rt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 12:13:16 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/29 02:02:14 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_shape(t_shapes *shapes)
{
	shapes->cylinder = NULL;
	shapes->sphere = NULL;
	shapes->plane = NULL;
	shapes->capsule = NULL;
}

void	initiaize_numbers_of_shapes(t_shapes *shapes)
{
	shapes->cylinder = NULL;
	shapes->plane = NULL;
	shapes->sphere = NULL;
	shapes->capsule = NULL;
	shapes->ambient.nmb = 0;
	shapes->light.nmb = 0;
	shapes->camera.nmb = 0;
	shapes->nmb_cy = 0;
	shapes->nmb_sp = 0;
	shapes->nmb_plane = 0;
	shapes->nmb_capsule = 0;
}

void	read_from_file_sequel(char *gnl, t_shapes *shapes)
{
	if (gnl == NULL)
		print_error(NULL, NULL, "empty file\n", shapes);
	initiaize_numbers_of_shapes(shapes);
}

char	*read_from_file(t_shapes *shapes, int fd)
{
	char	*gnl;
	char	*all;
	char	*tmp;

	all = NULL;
	gnl = get_next_line(fd);
	read_from_file_sequel(gnl, shapes);
	while (gnl)
	{
		if (!(ft_strncmp(gnl, "\n", ft_strlen(gnl)) == 0))
		{
			if (all)
				tmp = ft_strdup(all);
			else
				tmp = ft_strdup("");
			free (all);
			all = ft_strjoin(tmp, gnl);
			free (tmp);
		}
		free (gnl);
		gnl = NULL;
		gnl = get_next_line(fd);
	}
	free (gnl);
	return (all);
}

int	check_file(char **av, t_shapes *shapes)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_error(NULL, NULL, "File descriptor error\n", shapes);
	return (fd);
}
