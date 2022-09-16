/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:16:03 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/16 20:22:54 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int is_adjacent(t_path *data, int room)
{
	if (data->adj_grid[q_peek()][room] && room != data->start)
		return (1);
	return(0);
}

int is_obstacle(int *paths, int room)
{
	if(paths[room] < 0)
		return (1);
	return(0);
}

int is_collision(int node_number)
{
	if (node_number > 0)
		return (1);
	return(0);
}

void q_add_adjacent(t_path *data, int *paths)
{
	int room;

	room = 0;
	while(data->room_count < room)
	{
		if(is_adjacent(data, room))
		{
			if (is_collision(paths[room]))
				q_enqueue(room * -1);
			if (!is_obstacle(paths, room))
			{
				paths[room] = q_peek();
				q_enqueue(room);
			}
		}
		room++;
	}
}
int *q_print_queue()
{
	int *queue;
	int size;
	int i;
	int collision;

	i = 0;
	queue = q_get_list();
	size = q_get_len();

	while(size > i)
	{
		if (queue[i] < 0)
		{
			collision = queue[i] * -1;
			free(queue);
			queue = NULL;
			return (collision);
		}
		++i;
	}
}

int q_get_next_collision()
{
	int *queue;
	int size;
	int i;
	int collision;

	i = 0;
	queue = q_get_list();
	size = q_get_len();

	while(size > i)
	{
		if (queue[i] < 0)
		{
			collision = queue[i] * -1;
			free(queue);
			queue = NULL;
			return (collision);
		}
		++i;
	}
	free(queue);
	queue = NULL;
	return (0);
}

int backtrack_collided_path(t_path *data, int *path, int collision)
{
	int next;
	int prev;

	prev = collision;
	next = path[collision];
	while (next != data->start)
	{
		path[prev] = 0;
		prev = next;
		next = path[prev];
	}
	return(prev);
}

void set_latest_path_obstacle(t_path *data, int collision_point, int *paths)
{
	int next;
	int visit;

	visit = collision_point;
	next = collision_point;
	while (next != data->start)
	{
		visit = next;
		next = paths[next];
		paths[visit] *= -1;
	}
}

int q_has_end(int end)
{
	int *queue;
	int size;
	int i;

	i = 0;
	queue = q_get_list();
	size = q_get_len();

	while(size > i)
	{
		if (queue[i] == end)
		{
			free(queue);
			queue = NULL;
			return(1);
		}
		++i;
	}
	free(queue);
	queue = NULL;
	return (0);
}

int is_end_path(t_path *data, int room, int *paths)
{
	if((data->adj_grid)[data->end][room] && paths[room])
		return (1);
	return(0);
}

int		is_new_path(t_path *data, int *old_paths, int *new_paths, int end)
{
	while(end != data->start)
	{
		if(new_paths[end])
			return(0);
		end = old_paths[end];
	}
	return (1);
}


void	cpy_new_path(t_path *data, int *old_paths, int *new_paths, int end)
{
	while(end != data->start)
	{
		new_paths[end] = old_paths[end];
		end = old_paths[end];
	}
}

void	remove_residue(t_path *data, int *paths)
{
	int *new_paths;
	int i;

	i = 0;
	new_paths = (int *)ft_memalloc(sizeof(int) * data->room_count);
	if (!new_paths)
		exit(1);

	q_add_queue(data->room_count);
	while(data->room_count > i)
	{
		if (is_end_path(data, i, paths))
			q_enqueue(i);
		++i;
	}
	while(!q_is_empty())
	{
		if (is_new_path(data, paths, new_paths, q_peek()))
			cpy_new_path(data, paths, new_paths, q_peek());
		q_dequeue();
	}		
	ft_memmove(paths, new_paths, sizeof(int) * data->room_count);
	free(new_paths);
	new_paths = NULL;
	q_delete_queue();
}

void q_pop_collisions(t_path *data, int *paths)
{
	int *new_paths;
	int new_root_node;
	int collision;

	collision = q_get_next_collision();
	while (collision)
	{
		new_paths = dup_path(paths, data->room_count);
		new_root_node = backtrack_collided_path(data, new_paths, collision);
		new_paths[collision] = q_peek();
		remove_residue(data, new_paths);
		set_latest_path_obstacle(data, collision, new_paths);
		bfs(data, new_paths, new_root_node);
		q_pop(collision * -1);
		collision = q_get_next_collision();
	}
}


void remove_obstacles(int *paths, int paths_size)
{
	int i;

	i = 0;
	while (i < paths_size)
	{
		if (paths[i] < 0)
			paths[i] *= -1;
		++i;
	}
}

void bfs(t_path *data, int *paths, int root_node)
{
	q_add_queue(data->room_count);
	q_enqueue(root_node);
	while(!q_is_empty())
	{
		q_add_adjacent(data, paths);
		if (q_has_end(data->end))
		{
			remove_obstacles(paths, data->room_count);
			remove_residue(data, paths);
			get_winner(data, &data->best_path, paths);
			break;
		}
		q_pop_collisions(data, paths);
		q_dequeue();
	}
	q_delete_queue();
}