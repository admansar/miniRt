/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <selkahdr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:27:45 by selkhadr          #+#    #+#             */
/*   Updated: 2023/08/27 15:47:13 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void	ft_atof_sequel(char *str, int *i, int *d)
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
	int		i;
	int		count;
	double	sa;
	int		d;

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
	return (count * (d + sa));
}
