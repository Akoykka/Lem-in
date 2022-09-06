/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/06 18:56:10 by akoykka          ###   ########.fr       */
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

void queue_add_room(t_queue *q, int room_number)
{
	q->queue[q->size] = room_number;
	++q->size;
}

void queue_add_end_neighbours(t_path *data, char *paths, t_queue *q)
{
	q->size = 0;

	q->queue = (int *)ft_memalloc(sizeof(int) * data->room_count + 1);
	if (!q->queue)
		exit(1);
	


}

char *dup_paths(t_path *data, char *paths)
{
	t_queue q;
	int *dup;
	int room_number;
	int temp;

	queue_add_end_neighbours(data, paths, &q);
	room_number = 0;
	dup = (int *)ft_memalloc(sizeof(int)* data->room_count + 1);
	if (!dup)
		exit(1);
	while(q.size)
	{
		temp = q.queue;
		while(temp != START)
		{
		dup[temp] = paths[temp];
		if (dup[temp] < 0)
			dup[temp] *= -1;
		temp = paths[temp];
		if (temp < 0)
			temp *= -1;
		}
		queue_remove_head(&q);
	}
	return(dup);
}
int queue_add_adjacent(t_path *data, int *paths, t_queue *q)
{
	int room_number;

	room_number = 0;
	while(data->room_count < room_number)
	{
		if(ADJ_GRID[*(q->queue)][room_number] && room_number != END && room_number != START)
		{
			if (is_collision(paths[room_number]))
				queue_add_room(q, room_number * -1);
			
			if (!paths[room_number])
			{
				paths[room_number] = *(q->queue);
				queue_add(q, room_number);
			}
			
		}
		room_number++;
	}
}

void set_latest_path_visited(int collision_point, int *paths)
{
	int next;
	int visit;

	visit = 0;
	next = collision_point;
	while (next != START)
	{
		visit = next;
		next = paths[next];
		paths[visit] *= -1;
	}
}

void queue_remove_collision(int collision, t_queue *q)
{
	int i;

	i = 0;
	while (q->size > i && (q->queue)[i] != collision)
		++i;
	ft_memmove((q->queue)[i], (q->queue)[i + 1], sizeof(int) * (q->size - i));
	--q->size;
}

int is_collision(int node_number)
{
	if (node_number > 0)
		return (1);
	return(0);
}
void visit_node(int node, int *path, int parent_room)
{
	path[node] = parent_room;
}


void remove_duplicates(t_path *data, int *paths, int number)
{
	int room_number;

	room_number = number + 1;
	while (room_number < data->room_count)
	{
		if (paths[room_number] == number
		|| paths[room_number] == number * -1) /// possible thingy for negative numbers
			paths[room_number] = 0;
	}
}

void clean_bfs_residue(t_path *data, int *paths)
{
	int room_number;

	room_number = 2;
	while (room_number < data->room_count)
	{
		if (ADJ_GRID[END][room_number])
			remove_duplicates(data, paths, room_number);
		++room_number;
	}
}


void handle_reroutes(t_path *data, int *paths, t_queue *q)
{
	int *new_path;
	int reroute_node;
	int i;

	i = 0;
	while (q->size > i)
	{
		if (is_collision((q->queue)[i]))
		{
			new_path = (int *)ft_memalloc(sizeof(int) * data->room_count + 1);
			if (!new_path)
				exit(1);
			reroute_node = find_start_node(paths, (q->queue)[i]);
			visit_node(i, new_path, (*q->queue) * -1);
			new_path = dup_paths(data, paths);
			clean_bfs_residue(data, paths);
			set_latest_path_visited((q->queue)[i], new_path);
			bfs(data, new_path, reroute_node);
			queue_remove_collision((q->queue)[i], q);
		}
	}
}

void bfs(t_path *data, char *paths, int root_node)
{
	t_queue q;

	q.size = 1;
	q.queue = (int *)ft_memalloc(sizeof(int) * (data->room_count + 1));
	q.queue[0] = root_node;
	while(q.size)
	{
		queue_add_adjacent(data, paths, &q);
		queue_handle_reroutes(data, paths, &q);
		if (is_end_reached(&q, ))/// i dunno
		{
			clean_bfs_residue(data, paths);
			get_winner(data, *(data->best_path), paths);
			q.size = 0;
		}
		queue_remove_head(&q);
	}
	free(q.queue);
}



void queue_empty_start_neighbours(t_path *data, t_queue *q)
{
	int room_number;

	room_number = START;
	while(data->room_count > room_number)
	{
		if (data->adj_grid[START][room_number])
			queue_add(q, room_number);
		++room_number;
	}
}

// if number has previous node data (0 or higher)

void get_paths(t_path *data)
{
	t_queue	q;
	int		*paths;

	q.queue = (int *)ft_memalloc((sizeof(int) * data->room_count + 1));
	paths = (int *)ft_memalloc((sizeof(int) * data->room_count + 1));
	if (!q.queue || !paths)
		exit (1);
	queue_start_neighbours(data, &q);
	while (q.size)
	{
			bfs(data, paths, q.queue);
			queue_remove_head(&q);
	}
	free(q.queue);
}

int main(void)
{
	t_path data;

	read_input(&data);
	get_paths(&data);
	march_ants();
	exit (0);
}