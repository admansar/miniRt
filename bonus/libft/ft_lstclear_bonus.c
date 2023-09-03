/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:30:50 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/20 01:32:22 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*p;

	tmp = *lst;
	p = *lst;
	if (!lst && !del)
		return ;
	while (tmp != NULL || !del)
	{
		p = tmp;
		tmp = tmp->next;
		del(p->content);
		free(p);
	}
	*lst = NULL;
}
