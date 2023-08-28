/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 08:10:07 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/27 15:36:53 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
