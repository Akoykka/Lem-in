/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/31 21:04:46 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "lem_in.h"

int get_min_cut(data)
{
	int i;
	int min_cut_start;
	int min_cut_sink;

	i = 0;
	min_cut_start = 0;
	min_cut_sink = 0;
	while (i < ROOM_COUNT)
	{
		if (ADJ_GRID[START][i])
			++min_cut_start;
		++i;
	}
	i = 0;
	while (i < ROOM_COUNT)
	{
		if (ADJ_GRID[SINK][i])
			++min_cut_sink;
		++i;
	}
	if (min_cut_sink < min_cut_start)
		return (min_cut_sink);
	return(min_cut_start);
}

int is_adjacent(t_path *data, int room, int room2)
{
	if (ADJ_GRID[room][room2] == ADJACENT)
		return (1);
	return (0);
}

void queue_add(data, room_number)
{
	QUEUE[Q_SIZE] = room_number;
	Q_SIZE++;
}

void queue_remove_head(t_queue *queue)
{
	ft_memmove(queue->queue[1], queue->queue, sizeof(int) * queue->q_size);
	queue->q_size--;
}

get_new_path()



// if number has previous node data (0 or higher)

void get_paths(t_path *data)
{
	//int		min_cut;
	t_queue	start_node;
	int		path_found;

	//min_cut = get_min_cut(data);
	while(min_cut > path_count && path_found)
	{
		path_found = 0;
		get_start_adj_n_empty(data, &start_node);
		while (data->q_size)
		{
			if (get_new_path(data, start_node->queue))
				path_found = 1;
			queue_remove_head(&start_node)
		}
	}	
}

int main(int argc, char **argv)
{
	t_path data;

	argc -= 1;
	argv += 1;
	save_valid_rooms(&data, argc, argv);
	save_valid_links(&data, argc, argv);
	//trim_nodes(&data);
	get_paths(&data);`
	march_ants();
	//free_all();
	exit(1);
}