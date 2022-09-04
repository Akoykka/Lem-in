/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/04 16:28:25 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "lem_in.h"

int is_adjacent(t_path *data, int room, int room2)
{
	if (ADJ_GRID[room][room2] == ADJACENT)
		return (1);
	return (0);
}

void queue_remove_head(t_queue *q)
{
	if (!q->size)
		return ;
	ft_memmove(&(q->queue[1]), q->queue, sizeof(int) * q->size);
	q->size--;
}


int pathlen(int *paths, int node)
{
	int len;

	len = 0;
	while (node != START)
	{
		node = paths[node];
		++len;
	}
	return (len);

}

int get_turn_count(int ants, t_turns *turns)
{
	int ant_cap;

	ant_cap = turns->path_count * turns->longest_len - turns->total_len;
	
	if (ants - ant_cap <= 0)
		return(calc_small_ant_amount_turn_count);
	if ((ants - ant_cap) % turns->path_count)
		return ((ants - ant_cap) / turns->path_count + 1) ;
	return ((ants - ant_cap) / turns->path_count);
}


int calc_turns(t_path *data, int *paths)
{
	int i;
	int path_len;
	t_turns turn_count;

	i = 0;
	ft_memset(&turn_count, 0, sizeof(t_turns));
	while(data->room_count > i)
	{
		if (ADJ_GRID[END][i] && paths[i])
		{
			path_len = pathlen(paths, i);
			if (path_len > turn_count.longest_len)
				turn_count.longest_len = path_len;
			turn_count.total_len += path_len;
			++turn_count.path_count;
		}		
		++i;
	}
	return(get_turn_count(data->ant_count, &turn_count));
}


int get_winner_paths(t_path *data, int **best, int *contender)
{
	if (!*best || calc_turns(data, contender) < calc_turns(data, *best))
	{
		free(*best);
		*best = contender;
		return (1);
	}
	free(contender);
	contender = NULL;
	return (0);
}

char *cpy_paths(t_path *data, char *paths, int collision_point)
{
	char *new;

	new = 
	if (!new)
		exit (1);
	paths[collision_point]


}


char *bfs(t_path *data, char *paths, int root_node)
{
	t_queue q;
	int *best;
	int *contender;

	q.size = 1;
	q.queue[0] = root_node;
	paths[root_node] = START;
	while(q.size)
	{	
		queue_add_unvisited_neighbours();
		queue_remove_head();
		if (is_collision(data, paths, q.queue))
		{
			contender_paths = (int *)ft_memalloc(sizeof(int) * data->room_count);
			visit the copy on collision_point
			visit collisionpoint(mark prev on new)
			copy newpath to only completed paths + current path being built
			visit new_path_till the collision point including the collision
			clear_collided_path_to_the_start_of_path
			contender = bfs start of collided_path
			compare the best free the worse save better;
		}
		else (queue includes end_node_neighbours)
			make comparison;
	}
	if(best = NULL)
		return NULL;
	return (best);
}

int alter_paths(t_path *data, int start_node)
{
	int *best;
	int *contender;
	t_queue q;
	int path_altered;

	path_altered = 0;
	best = NULL;
	fill_queue(data, &q);
	while(q.size)
	{
		contender = bfs(data, data->paths, q.queue);
		if (get_winner_paths(data, &best, contender))
			path_altered = 1;
	}
	return (path_altered);
}

void queue_add_room(t_queue *q, int room_number)
{
	q->queue[q->size] = room_number;
	++q->size;
}
void queue_empty_start_neighbours(t_path *data, t_queue *q)
{
	int room_number;

	room_number = 0;
	while(data->room_count > room_number)
	{
		if(data->adj_grid[START][room_number] && !(data->paths)[room_number])
			queue_add(q, room_number);
	}
}

// if number has previous node data (0 or higher)

void get_paths(t_path *data)
{
	t_queue	q;
	int		paths_altered;

	q.queue = (int *)ft_memalloc((sizeof(int) * data->room_count + 1));
	if (!q.queue)
		exit (1);
	paths_altered = 1;
	while (paths_altered)
	{
		paths_altered = 0;
		queue_empty_start_neighbours(data, &q);
		while (q.size && !paths_altered)
		{
			if (alter_paths(data, q.queue))
				paths_altered = 1;
			relax_visited(data);
			queue_remove_head(&q);
		}
	}
	free(q.queue);
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