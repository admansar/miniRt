/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admansar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:11:42 by admansar          #+#    #+#             */
/*   Updated: 2023/08/28 17:11:56 by admansar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	free_all(t_all *all)
{
	free(all->cylinder);
	free(all->capsule);
	free(all->sphere);
	free(all->plan);
}
