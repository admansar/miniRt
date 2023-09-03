/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selkhadr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:37:11 by selkhadr          #+#    #+#             */
/*   Updated: 2022/10/20 01:39:16 by selkhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*p;
	t_list	*node;

	tmp = lst;
	p = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (tmp != NULL)
	{
		node = ft_lstnew(f(tmp->content));
		ft_lstadd_back(&p, node);
		if (!node->content)
			ft_lstclear(&p, del);
		tmp = tmp->next;
	}
	return (p);
}
