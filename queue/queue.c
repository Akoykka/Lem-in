/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 12:31:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/11 00:14:43 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

void q_init(int size)
{
	t_queue *q_list;

	q_list = q_get();
	if (q_list->queue)
		++q_list;
	q_list->queue = (int *)ft_memalloc(sizeof(int) * size);
	q_list->size = size;
}

void q_destroy()
{
	t_queue *q_list;

	q_list = q_get();
	if (q_list->queue)
	{
		free(q_list->queue);
		q_list->queue = NULL;
	}
}

void	q_enqueue(int content)
{
	t_queue *q;

	q = q_get();
	q->queue[q->size] = content;
	++q->size;
}

void	q_dequeue(void)
{
	t_queue *q;

	q = q_get();
	if (q->size)
	{
		ft_memmove(q->queue, (q->queue) + 1, q->size - 1);
		--q->size;
	}
}
int q_get_len()
{
	t_queue *q;

	q = q_get();
	return (q->size);
}

int *q_get_list()
{
	t_queue *q;
	int *list;

	q = q_get();
	if (q->size)
	{
		list = (int *)ft_memalloc(sizeof(int) * q->size);
		if (!list)
			exit(1);
	}
	ft_memcpy(list, q->queue, sizeof(int) * q->size);
	return (list);
}

int q_peek(void)
{
	t_queue *q;

	q = q_get();
	if (!q->size)
	{
		ft_putstr("exiting...is empty (q_peek)\n");
		exit (1);
	}
	return (*(q->queue));
}
int q_is_empty()
{
	t_queue *q;

	q = q_get();
	if (!q->size)
		return (1);
	return(0);
}

t_queue *q_get(void)
{
	t_queue *q_list;
	size_t i;

	i = 1;
	q_list = q_static();
	while(q_list->queue)
	{
		++q_list;
		++i;
		if(i > 1024)
		{
			ft_putstr("queues_full\n");
			exit(1);
		}
	}
	return (&q_list[i - 1]);
}

t_queue *q_static()
{
	static t_queue	queue_list[1024];
	return(queue_list);
}