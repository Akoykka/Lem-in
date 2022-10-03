/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 12:31:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/10/03 12:12:16 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/queue.h"

t_qdata	*q_new(unsigned int max_size)
{
	t_qdata	*new;

	new = (t_qdata *)ft_memalloc(sizeof(t_qdata));
	new->queue = ft_memalloc(sizeof(int) * max_size + 1);
	new->size = 0;
	return (new);
}

void	q_init(void)
{
	t_queue_storage	*temp;

	temp = q_storage();
	temp->queue_list = (t_qdata **)ft_memalloc(sizeof(t_qdata *) * 4000);
	if (!temp->queue_list)
		exit (1);
	temp->list_size = 4000;
}

void	q_extend_memory(void)
{
	t_queue_storage	*temp;
	t_qdata			**new_list;
	unsigned int	i;

	temp = q_storage();
	i = 0;
	new_list = (t_qdata **)ft_memalloc(sizeof(t_qdata *) * temp->list_size * 2);
	if (!new_list)
		exit (1);
	while (i < temp->current_list)
	{
		new_list[i] = temp->queue_list[i];
		++i;
	}
	free (temp->queue_list);
	temp->queue_list = new_list;
}

void	q_add_queue(unsigned int size)
{
	t_queue_storage	*temp;

	temp = q_storage();
	if (temp->list_size)
		++temp->current_list;
	if (temp->list_size == temp->current_list)
		q_extend_memory();
	temp->queue_list[temp->current_list] = q_new(size);
	if (!temp->queue_list[temp->current_list])
		exit (1);
}

void	q_delete_queue(void)
{
	t_queue_storage	*temp;

	temp = q_storage();
	if (temp->list_size)
	{
		free ((temp->queue_list)[temp->current_list]);
		(temp->queue_list)[temp->current_list] = NULL;
		if (temp->current_list)
			--temp->current_list;
	}
}

void	q_enqueue(int content)
{
	t_qdata	*q;

	q = q_get();
	(q->queue)[q->size] = content;
	++(q->size);
}

void	q_dequeue(void)
{
	t_qdata	*q;

	q = q_get();
	if (q->size)
	{
		ft_memmove(q->queue, (q->queue + 1), sizeof(int) * q->size);
		--q->size;
	}
}

int	q_get_len(void)
{
	t_qdata	*q;

	q = q_get();
	return (q->size);
}

int	*q_get_list(void)
{
	t_qdata	*q;
	int		*list;

	list = NULL;
	q = q_get();
	if (q->size)
	{
		list = (int *)ft_memalloc(sizeof(int) * q->size);
		if (!list)
			exit (1);
		ft_memcpy(list, q->queue, sizeof(int) * q->size);
	}
	return (list);
}

int	q_peek(void)
{
	t_qdata	*q;

	q = q_get();
	if (!q->size)
	{
		ft_putstr("exiting...is empty (q_peek)\n");
		exit (1);
	}
	return (*(q->queue));
}

int	q_is_empty(void)
{
	t_qdata	*q;

	q = q_get();
	if (!q || !q->size)
		return (1);
	return (0);
}

void	q_bzero(void)
{
	t_qdata	*temp;

	temp = q_get();
	ft_bzero(temp->queue, sizeof(int) * temp->size);
	temp->size = 0;
}

void	q_pop(int content)
{
	t_qdata			*q;
	unsigned int	i;

	i = 0;
	q = q_get();
	while ((q->queue)[i] != content)
	{
		++i;
		if (i == q->size)
		{
			ft_putstr("content not found (q_pop");
			exit (1);
		}
	}
	ft_memmove(&q->queue[i], &q->queue[i+1], (sizeof(int) * (q->size - i)));
	--q->size;
}

void	q_destroy(void)
{
	t_queue_storage	*temp;
	unsigned int	i;

	i = 0;
	temp = q_storage();
	if (!temp || temp->queue_list)
		return ;
	while (i < temp->current_list)
	{
		free((temp->queue_list)[i]);
		(temp->queue_list)[i] = NULL;
	}
	free(temp->queue_list);
	temp->queue_list = NULL;
	temp->current_list = 0;
	temp->list_size = 0;
}

t_qdata	*q_get(void)
{
	t_queue_storage	*temp;

	temp = q_storage();
	return ((temp->queue_list)[temp->current_list]);
}

t_queue_storage	*q_storage(void)
{
	static t_queue_storage	storage;

	return (&storage);
}
