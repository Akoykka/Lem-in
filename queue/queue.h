/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:40:59 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/12 21:23:30 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H
# include "../libft/includes/libft.h"

typedef struct s_qdata
{
	int				*queue;
	unsigned int	size;
}			t_qdata;

typedef struct	s_queue_storage
{
	t_qdata			**queue_list;
	unsigned int	current_list;
	unsigned int	list_size;
	
}			t_queue_storage;

// INIT
void	q_init();
void	q_add_queue(unsigned int max_size);
void	q_delete_queue();
void	q_destroy();

// STORAGE
t_queue_storage *q_storage();
t_qdata *q_get(void);

// FUNCTIONS
void	q_enqueue(int content);
void	q_dequeue(void);
int		q_peek(void);
void	q_pop(int content);
int 	q_is_empty();
int		*q_get_list();
int 	q_get_len();

#endif