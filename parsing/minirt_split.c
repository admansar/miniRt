/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 08:10:07 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/28 15:49:18 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_shapes(t_shapes *shapes)
{
	if (shapes->cylinder)
	{
		free (shapes->cylinder);
		shapes->cylinder = NULL;
	}
	if (shapes->sphere)
	{
		free (shapes->sphere);
		shapes->sphere = NULL;
	}
	if (shapes->plane)
	{
		free (shapes->plane);
		shapes->plane = NULL;
	}
	if (shapes->capsule)
	{
		free (shapes->capsule);
		shapes->capsule = NULL;
	}
	if (shapes)
		free (shapes);
}

static int	minirt_len(char *s)
{
	int	l;
	int	i;

	l = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		else
		{
			while (s[i] && (s[i] != ' ' && s[i] != '\t'))
				i++;
			l++;
		}
	}
	return (l);
}

char	**minirt_split(char *s)
{
	char	**p;
	int		k;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (!s)
		return (NULL);
	p = (char **)malloc((minirt_len((char *)s) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (s[i])
	{
		while (s[i] && (s[i] == ' ' || s[i] == '\t'))
			i++;
		k = i;
		while (s[i] && (s[i] != ' ' && s[i] != '\t'))
			i++;
		if (l < minirt_len((char *)s))
			p[l++] = ft_substr(s, k, i - k);
	}
	p[l] = NULL;
	return (p);
}
