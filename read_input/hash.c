/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:03:31 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/08 13:21:46 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"

/*
	every cycle of hash function
	Bitshift is faster on cpu ((hash << 5) + hash)
*/

unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	while (*str)
	{
		c = *str;
		hash = hash * 33 + c;
		++*str;
	}
	return (hash % HASH_SIZE);
}

int hash_check_collision(t_hash *hash_table, t_path *data, unsigned long digest)
{
	if (digest == HASH_SIZE - 1)
		digest = 0;
	else
		++digest;
	if(hash_table[digest])
		return(1);
	return(0);
}

int search_name_list(t_path *data, char *room_name)
{
	int i;

	i = 0;
	while(data->room_count > i)
	{
		if (!ft_strcmp((char *)room_name, (data->name_list)[i]))
			return (i);
	}
	printf("ERROR NAME NOT FOUND(search_name_list");
	exit(1);
	//// sort this out;
	return(1);
}


unsigned long get_room(t_path *data, char *str)
{
	unsigned long digest;

	digest = hash(str);
	if (hash_check_collision(data, digest))
		return (search_name_list(data, str));
	else
		return ((data->hash_table)[digest]);

}


void save_room(t_path *data, char *room_name, int y, int x)
{
	unsigned long digest;
	y = 0;
	x = 0;

	digest = hash(room_name);
	while ((data->hash_table)[digest])
	{
		++digest;
		if (digest == HASH_SIZE)
			digest = 0;
	}
	data->hash_table[digest] = data->room_count;
	if (!data->hash_table[digest])
		exit(1);
}

void save_link(t_path *data, char *room_name, char *room2_name)
{
	unsigned long node1;
	unsigned long node2;
	node1 = get_room(data, room_name);
	node2 = get_room(data, room2_name);
	(data->adj_grid)[node1][node2] = 1;
	(data->adj_grid)[node2][node1] = 1;
}








Take input

use hashtable to do it ;


we need:

Room count for iteration
adj_matrix as the map

antcount for the evaluation

start and end
