/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:27:45 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/29 01:45:17 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	help(void)
{
	ft_putstr_fd("\033[0;31mError, no file added as a \
	argument or the file is not a .rt type\n", 2);
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

double	_continue(int i, char *str, t_shapes *shapes)
{
	double	c;
	double	sa;

	if (str == NULL)
		return (0);
	if (str[i] == '.')
		i++;
	else
	{
		if (str[i] != '\0' && str[i] != '\n')
			print_error(NULL, NULL, "not a valid nmb\n", shapes);
	}
	c = 1;
	sa = 0;
	while (str[i] >= 48 && str[i] <= 57 && str[i])
	{
		c = c / 10;
		sa = sa + c * (str[i] - 48);
		i++;
	}
	if (!(str[i] >= 48 && str[i] <= 57) && str[i] && str[i] != '\n')
		print_error(NULL, NULL, "not a valid nmb\n", shapes);
	return (sa);
}

void	ft_atof_sequel(char *str, int *i, long int *d)
{
	while (str[*i] >= 48 && str[*i] <= 57 && str[*i])
	{
		*d = *d * 10;
		*d = *d + str[*i] - 48;
		(*i)++;
	}
}

double	ft_atof(char *str, t_shapes *shapes)
{
	int			i;
	int			count;
	double		sa;
	long int	d;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	d = 0;
	count = 1;
	if (str[i] == '-')
	{
		count = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	ft_atof_sequel(str, &i, &d);
	sa = _continue(i, str, shapes);
	if (d > INT_MAX)
		exit (1);
	return (count * (d + sa));
}
