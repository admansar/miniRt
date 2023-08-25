/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:50:47 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/19 16:25:12 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*gnl_strchr(char *s, char c)
{
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	while (c != *str)
	{
		if (!(*str))
			return (0);
		str++;
	}
	return (str);
}

char	*gnl_substr(char *s, int start, int len)
{
	char	*p;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[start] && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*gnl_strjoin(char *r, char *buffer)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (gnl_strlen(buffer) == 0)
		return (NULL);
	p = (char *)malloc(gnl_strlen(r) + gnl_strlen(buffer) + 1);
	if (!p)
		return (NULL);
	while (r && r[i])
	{
		p[i] = r[i];
		i++;
	}
	while (buffer && buffer[j])
		p[i++] = buffer[j++];
	p[i] = '\0';
	free (r);
	return (p);
}

char	*fill_s(char *str)
{
	int		slash_n;
	char	*s;

	slash_n = back_slash_len(str);
	s = gnl_substr(str, slash_n, gnl_strlen(str) - slash_n);
	return (s);
}
