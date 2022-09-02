/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/01 22:23:30 by akoykka          ###   ########.fr       */
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

int calc_turns(t_path *data, int *paths)
{
	ants / path_count + path_count + lenght
	




}


int get_winner_paths(t_path *data, int *best, int *contender)
{
	if (calc_turns(data, contender) < calc_turns(data, best))
	{
		free(best);
		best = contender;
		return (1);
	}
	free(contender);
	contender = NULL;
	return (0);
}



int is_there_new_path(t_path *data, int start_node)
{
	int *best_path;
	int *contender;
	t_queue q;

	best_path = NULL;
	fill_queue(data, &q);
	while(q.size)
	{

		queuemanipulation
		contender = bfs(data, q.queue)
		get_winner_paths(data->ant_count, best_path, contender);
	}


}

void queue_empty_start_neighbours(t_path *data, t_queue *q)
{




}

// if number has previous node data (0 or higher)

void get_paths(t_path *data)
{
	//int		min_cut;
	t_queue	q;
	int		path_found;

	//min_cut = get_min_cut(data); while(min_cut > path_count
	path_found = 1;

	while(path_found)
	{
		path_found = 0;
		queue_empty_start_neighbours(data, &q);
		while (q.size)
		{
			if (is_there_new_path(data, q.queue))
				path_found = 1;
			relax_visited(data);
			queue_remove_head(&q)
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
	get_paths(&data);
	march_ants();
	//free_all();
	exit(1);
}