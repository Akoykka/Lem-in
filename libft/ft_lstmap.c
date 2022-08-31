/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:35:44 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/03 09:42:43 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	ft_del(void *content, size_t content_size)
{
	ft_bzero(content, content_size);
	free(content);
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*newhead;
	t_list	*previous;

	if (!lst || !f)
		return (NULL);
	newhead = f(lst);
	if (!newhead)
		return (NULL);
	temp = newhead;
	lst = lst->next;
	while (lst)
	{
		temp->next = f(lst);
		if (!temp->next)
		{
			ft_lstdel(&newhead, &ft_del);
			return (NULL);
		}	
		previous = temp;
		temp = temp->next;
		lst = lst->next;
	}
	previous = NULL;
	return (newhead);
}
