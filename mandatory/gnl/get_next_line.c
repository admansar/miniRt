/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:39:09 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/19 15:20:20 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	back_slash_len(char *buffer)
{
	int		i;
	char	*p;

	p = gnl_strchr(buffer, '\n');
	if (!buffer)
		return (0);
	i = 0;
	while (buffer + i <= p)
		i++;
	return (i);
}

char	*check_buffer(char *buffer)
{
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	return (buffer);
}

char	*check_s(char *s, char *r)
{
	r = gnl_strjoin(r, s);
	free(s);
	return (r);
}

char	*check_r(char *stc, char *r, char *buffer, int fd)
{
	int	red;

	red = 1;
	while (gnl_strchr(buffer, '\n') == NULL)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red == 0 && stc != NULL)
		{
			free (stc);
			stc = NULL;
		}
		if (red <= 0)
			break ;
		buffer[red] = '\0';
		r = gnl_strjoin(r, buffer);
	}
	return (r);
}

char	*get_next_line(int fd)
{
	char		*r;
	char		*tmp;
	static char	*s;
	char		*buffer;

	buffer = NULL;
	if (fd < 0)
		return (NULL);
	r = NULL;
	if (s)
	{
		r = check_s(s, r);
		s = NULL;
	}
	buffer = check_buffer(buffer);
	r = check_r(s, r, buffer, fd);
	if (gnl_strchr(r, '\n'))
	{
		tmp = r;
		r = gnl_substr(r, 0, back_slash_len(r));
		s = fill_s(tmp);
		free(tmp);
	}
	free(buffer);
	return (r);
}
