/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:16:03 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/22 19:23:37 by akoykka          ###   ########.fr       */
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

void q_add_adjacent(t_path *data, int *paths, int *residue)
{
	int room;

	room = 0;
	while(data->room_count > room)
	{
		if(is_adjacent(data, room) && !is_WHAT(paths, room))
		{
			residue[room] = q_peek();
			q_enqueue(room);
		}
		room++;
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

void	visit_start_nodes(t_path *data, int *path)
{
	int i;

	i = 0;
	while (data->room_count > i)
	{
		if (data->adj_grid[data->start][i])
			path[i] = -1;
		++i;
	}
}

int bfs(t_path *data)
{
	q_add_queue(data->room_count);
	q_enqueue(data->start);
	while(!q_is_empty())
	{
		q_add_adjacent(data, paths);
		if (q_has_end(data->end))
		{
			cpy_path(data->best);
			return (0);
		}
		q_dequeue();
	}
	q_delete_queue();
	return(1);
}

void residue(t_path *data, int *paths, int *residue, int start)
{
	q_add_queue(data->room_count);
	q_enqueue(start);
	while(!q_is_empty())
	{
		q_add_adjacent(data);

		if(not visited)
			if(existing path (points to negative index))
				temp = where it points and then visit current node
				goto temp;
			if (empty_path)
				visit node
			
	}
	write_residue_to_paths;
}




Tarvitaan:
int *cpy_path(t_path *data, int *paths); 
	ottaa int *arrayn kopioi vaan pathit;

int *make_residue(t_path *data, int *paths); 
	tekee pathfilusta "peilikuvan" ;
	peilikuvan pointterit negatiivisilla numeroilla;
	paitsi startin vieressa olevat positiivisina ;
	ja end (valmiiksi visitoitu);



