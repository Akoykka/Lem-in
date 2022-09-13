/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 20:12:06 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/13 17:28:39 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "queue.h"

void print_queue(void)
{
	int loop;
	int *queue;
	loop = q_get_len();
	queue = q_get_list();
	printf("QLEN = %i  ", q_get_len());
	printf("Queue is: \t");
	while(loop--)
	{
		printf("%i\t", *queue);
		++queue;
	}
	printf("\n");
}

int main(void)
{
	q_init();
	q_add_queue(30);
	q_enqueue(13);
	q_enqueue(2);
	q_enqueue(3);
	print_queue();
	q_enqueue(5);
	print_queue();
	q_add_queue(30);
	q_enqueue(19);
	q_enqueue(1);
	q_enqueue(1);
	print_queue();
	q_delete_queue();
	print_queue();
	q_dequeue();
	q_delete_queue();
	q_add_queue(30);
	q_enqueue(1);
	q_enqueue(666);
	q_enqueue(3);
	q_pop(666);
	print_queue();
	printf("\nQPEEK IS = %i\n", q_peek());


	
	//printf("is_empty:%i\n", q_is_empty());
}