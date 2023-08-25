/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 19:32:46 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/23 19:19:48 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	check_file(int ac, char **av, t_shapes *shapes)
{
	int	len;
	int	fd;

	if (ac != 2)
		print_error(NULL, NULL, "file name required", shapes);
	len = ft_strlen(av[1]) - 3;
	if (ft_strncmp(av[1] + len, ".rt", ft_strlen(av[1] + len)))
		print_error(NULL, NULL, ".rt file required", shapes);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_error(NULL, NULL, "here4", shapes);
	return (fd);
}

void	calcul_nmbr_of_shapes(char **all, t_shapes *shapes)
{
	char	**split;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(*all, '\n');
	while (tmp[i])
	{
		split = minirt_split(tmp[i]);
		if (ft_strncmp(split[0], "cy", ft_strlen(split[0])) == 0)
			shapes->nmb_cy++;
		else if (ft_strncmp(split[0], "sp", ft_strlen(split[0])) == 0)
			shapes->nmb_sp++;
		else if (ft_strncmp(split[0], "pl", ft_strlen(split[0])) == 0)
			shapes->nmb_plane++;
		free_double_array(split);
		i++;
	}
	shapes->cylinder =ft_calloc(shapes->nmb_cy + 1, sizeof(t_cylinder_info));
	shapes->sphere = ft_calloc(shapes->nmb_sp + 1, sizeof(t_sphere_info));
	shapes->plane = ft_calloc(shapes->nmb_plane + 1, sizeof(t_plane_info));
	i = 0;
	while (tmp[i])
	{
		split = minirt_split(tmp[i]);
		shapes_fnct(shapes, split);
		free_double_array(split);
		i++;
	}
	free_double_array(tmp);
}

int help(void)
{
	ft_putstr_fd("\033[0;31mError, no file added as a argument or the file is not a .rt type\n", 2);
	return (1);
}

int	ft_strncmp_dual(const char *s1, const char *s2, size_t n)
{
	int	len1;
	int	len2;

	if ((!s1 && !s2) || !n)
		return (0);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	if (!len1 || !len2)
		return (0);
	while (len1-- && len2-- && n--)
	{
		if (((unsigned char *)s1)[len1] > ((unsigned char *)s2)[len2])
			return (1);
		if (((unsigned char *)s1)[len1] < ((unsigned char *)s2)[len2])
			return (-1);
		if (len1 == 0 || len2 == 0 || n == 0)
			return (0);
	}
	return (0);
}


void init_shape(t_shapes *shapes)
{
	shapes->cylinder = NULL;
	shapes->sphere = NULL;
	shapes->plane = NULL;
}


int	main(int ac, char **av)
{
	char			*gnl;
	int				fd;
	t_shapes		*shapes;
	char			*all;
	char			*tmp;

	if (ac != 2 || (ac == 2 && ft_strncmp_dual(av[1], ".rt", 4)))
		return (help());
	all = NULL;
	shapes = malloc(sizeof(t_shapes));
	init_shape(shapes);
	fd = check_file(ac, av, shapes);
	gnl = get_next_line(fd);
	initiaize_numbers_of_shapes(shapes);
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
	calcul_nmbr_of_shapes(&(all), shapes);
	minirt(shapes);
	free_shapes(shapes);
	return (0);
}
