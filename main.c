/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/07 12:31:12 by akoykka          ###   ########.fr       */
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

void queue_add_path_ends(t_path *data, char *paths, t_queue *q)
{
	int room_number;

	room_number = 0;
	q->size = 0;
	q->queue = (int *)ft_memalloc(sizeof(int) * data->room_count + 1);
	if (!q->queue)
		exit(1);
	while(data->room_count > room_number)
	{
		if (ADJ_GRID[END][room_number] && paths[room_number])
		{
			(q->queue)[q->size] = room_number;
			++q->size;
		}
	}
}

char *dup_paths(t_path *data, char *paths)
{
	t_queue q;
	int *dup;
	int room_number;
	int temp;

	queue_add_path_ends(data, paths, &q);
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

void set_latest_path_visited(int collision_point, int *paths)
{
	int next;
	int visit;

	visit = collision_point;
	next = collision_point;
	while (next != START)
	{
		visit = next;
		next = paths[next];
		paths[visit] *= -1;
	}
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

void clear_bfs_residue(t_path *data, int *paths)
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
			clear_bfs_residue(data, paths);
			new_path = dup_paths(data, paths);
			set_latest_path_visited((q->queue)[i], new_path);
			bfs(data, new_path, reroute_node);
			queue_remove_collision((q->queue)[i], q);
		}
	}
}

int is_end_reached(t_queue *q)
{
	int i;

	i = 0;
	while(q->size > i)
	{
		if ((q->queue)[i] == END)
			return (1);
		++i;
	}
	return (0);
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
		if (is_end_reached(&q))/// i dunno
		{
			clean_bfs_residue(data, paths);
			get_winner(data, *(data->best_path), paths);
		}
		queue_remove_head(&q);
	}
	free(q.queue);
}

// if number has previous node data (0 or higher)

void get_paths(t_path *data)
{
	t_queue	q;

	q.queue = (int *)ft_memalloc((sizeof(int) * data->room_count + 1));
	if (!q.queue || !paths)
		exit (1);
	queue_start_neighbours(data, &q);
	while (q.size)
	{
			if (data->path_changed)
			{
				data->path_changed = 0;
				q.size = 0;
				queue_start_neighbours(data, &q);
				if(!q.size)
				{
					free(q.queue);
					return; // here maybe free
				}
			}
			bfs(data, dup_paths(data, data->best_path), q.queue);
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