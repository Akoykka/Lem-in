/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/20 07:59:04 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void visit_node(int node, int *path, int parent_room)
{
	path[node] = parent_room;
}

void q_unused_root_nodes(t_path *data)
{
	int room;

	room = 0;
	while(data->room_count > room)
	{
		if ((data->adj_grid)[data->start][room]
			&&( !data->best_path || !(data->best_path)[room]))
			q_enqueue(room);
		++room;
	}
}

int *dup_path(int *path, int size)
{
	int	i;
	int *new;

	i = 0;
	new = (int *)ft_memalloc(sizeof(int) * size);
	if(!new)
		exit(1);
	if(!path)
		return(new);
	while (size > i)
	{
		if (path[i] < 0)
			new[i] = (path[i]) * -1;
		else
			new[i] = path[i];
		++i;
	}
	return (new);
}

void queue_paths_in_print(t_path *data)
{
	int i;

	i = 0;
	while(data->room_count > i)
	{
		if(data->adj_grid[data->end][i] && data->best_path[i])
		{
			q_enqueue(i);
		}
		++i;
	}
}

void print_neigbours(t_path *data, int room)
{
	int i;

	i = 0;
	printf("Room-name: |%s| index |%i| neighbours are: \n", data->room_list[room], room);
	while(data->room_count > i)
	{
		if(data->adj_grid[room][i])
			printf("Room name:|%s| index|%i|\n",data->room_list[i], i);
		++i;
	}
}


void print_paths(t_path *data)
{
	int i;
	int len;

	q_add_queue(data->room_count);
	queue_paths_in_print(data);
	while(!q_is_empty())
	{
		len = 0;
		i = q_peek();
		printf("path:");
		while (i != data->start && len < data->room_count)
		{
			printf("|%i|", i);
			i = data->best_path[i];
			++len;
		}
		printf("len: %i\n", len);
		q_dequeue();
	}
	printf("------------------\n");
	printf("Current Total Turns = %i\n\n", calc_turns(data, data->best_path));
	q_delete_queue();
}

void get_paths(t_path *data)
{
	q_add_queue(data->room_count);
	q_unused_root_nodes(data);
	while (!q_is_empty())
	{
			if (data->path_changed)
			{
				data->path_changed = 0;
				if (data->best_path)
					print_paths(data); ////// DEBUG
				q_bzero();
				q_unused_root_nodes(data);
			}
			bfs(data, dup_path(data->best_path, data->room_count), q_peek());
			q_dequeue();
	}
	q_destroy();
}





int main(void)
{
	t_path data;

	q_init();
	ft_memset(&data, 0, sizeof(data));
	read_input(&data);
	get_paths(&data);
	print_paths(&data);
	//march_ants();
	exit (0);
}