/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:04:55 by akoykka           #+#    #+#             */
/*   Updated: 2022/06/03 09:42:43 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_lstcount(t_list *start)
{
	size_t	i;
	t_list	*temp;

	i = 0;
	if (!start)
		return (i);
	temp = start;
	while (temp)
	{
		temp = temp->next;
		++i;
	}
	return (i);
}
