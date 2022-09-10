/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:40:59 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/10 23:28:35 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H
# include "../libft/includes/libft.h"

typedef struct s_queue
{
	int				*queue;
	int				size;
}			t_queue;

// INIT
t_queue *q_init(int size);
void	q_destroy();

// STORAGE
t_queue *q_static();
t_queue *q_get(void);

// FUNCTIONS
void	q_enqueue(int content);
void	q_dequeue(void);
int		q_peek(void);
void	q_pop(int content);
int 	q_is_empty();
int		*q_get_list();

#endif