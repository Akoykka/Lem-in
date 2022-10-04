/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/10/04 06:20:06 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	pathlen(int *paths, int node, int start)
{
	int	len;

	len = 0;
	while (node != start)
	{
		node = paths[node];
		++len;
	}
	return (len);
}

int	get_turn_count(int ants, t_turns *turns)
{
	int	ant_leak;

	ant_leak = turns->path_count * turns->longest_len - turns->total_len;
	if (ants - ant_leak <= 0) // If extra path does not reduce turn count
		return(9999999);
	if ((ants - ant_leak) % turns->path_count)
		return ((ants - ant_leak) / turns->path_count + 1 + turns->longest_len);
	return ((ants - ant_leak) / turns->path_count + turns->longest_len);
}

int	calc_turns(t_path *data, int *paths)
{
	int		i;
	int		path_len;
	t_turns	turn_count;

	i = 0;
	ft_memset(&turn_count, 0, sizeof(t_turns));
	while (data->end->links[i])
	{
		if (paths[data->end->links[i]->id])
		{
			path_len = pathlen(paths, data->end->links[i]->id, data->start->id);
			if (path_len > turn_count.longest_len)
				turn_count.longest_len = path_len;
			turn_count.total_len += path_len;
			++turn_count.path_count;
		}
		++i;
	}
	return (get_turn_count(data->ant_count, &turn_count));
}

void	get_winner(t_path *data)
{
	int	turns;

	turns = calc_turns(data, data->current_paths);
	if (data->winner_turns == -1
		|| turns < data->winner_turns)
	{
		ft_memmove(data->winner, data->current_paths, sizeof(int) * data->room_count);
		data->winner_turns = turns;
	}
}

void set_path_as_negative_value(t_path *data, int *paths, int end_point)
{
	while (paths[end_point] != data->start->id)
	{
			paths[end_point] *= -1;
			end_point = paths[end_point * -1];
	}
}

/*void remove_positive_trash(t_path *data, int *paths)
{
	int	i;

	i = 0;
	while(data->room_count > i)
	{
		if(paths[i] > 0)
			paths[i] = 0;
		if(paths[i] < 0)
			paths[i] *= -1;
		++i;
	}
}*/

void	bfs_trash_collector(t_path *data, int *paths)
{
	int i;
	int j;

	j = 0;
	while(data->end->links[j])
	{
		i = data->end->links[j]->id;
		while (i != data->start_id && i != 0)
		{
			paths[i] *= -1;
			i = paths[i] * -1;
		}
		j++;
	}
	i = 0;
	while (i < data->room_count)
	{
		if (paths[i] > 0)
			paths[i] = 0;
		if(paths[i] < 0)
			paths[i] *= -1;
		++i;
	}
}

/*void bfs_trash_collector(t_path *data, int *paths)
{
	t_hash *links;

	links = *(data->end->links);

	while(links)
	{
		if (paths[links->id])
			set_path_as_negative_value(data, paths, paths[links->id]);
		++links;
	}
	remove_positive_trash(data, paths);
}*/



/*

void	bfs_trash_collector(t_path *data, int *paths)
{
	int	i;
	int	j;

	i = 0;
	int y = 0;
	while (y < 360)
	{
		printf("paths[%d]: %d\n", y, paths[y]);
		y++;
	}
	while (data->end->links[i])
	{
		j = (data->end->links)[i]->id;
		while (paths[j] != data->start->id) //infinite loop
		{
			printf("j: %d\n", j);
			printf("paths[j]: %d\n", paths[j]);
			paths[j] *= -1;
			if (paths[j] < 0)
				j = paths[j] * -1;
			else
				j = paths[j];
			printf("j: %d\n", j);
			printf("paths[j]: %d\n", paths[j]);
			printf("paths[1]: %d\n", paths[1]);
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		if (paths[i] > 0)
			paths[i] = 0;
		i++;
	}
}
*/

int *q_get_ptr()
{
	t_qdata *temp;
	int *ptr;

	temp = q_get();
	ptr = temp->queue;
	return(ptr);
}

int end_has_been_reached(t_path *data, t_hash *current)
{
	int i;

	i = 0;
	while (current->links[i])
	{
		if (current->links[i] == data->end)
			return (1);
		i++;
	}
	return (0);
}

int	visit_non_residual_nodes(t_path *data, int *current_paths, int *residue)
{
	int *queue;
	t_hash **link;
	int i;
	int j;


	i = 0;
	queue = q_get_ptr();
	while (i < q_get_len())
	{
		link = data->room_list[queue[i]]->links;
		j = 0;
		while (link[j])
		{
			if (current_paths[link[j]->id] == 0
				&& residue[link[j]->id] == 0
				&& link[j]->id != data->start->id)
			{
				q_enqueue(link[j]->id);
				current_paths[link[j]->id] = queue[i];
				if (end_has_been_reached(data, data->room_list[link[j]->id]))
					return (1);
			}
			++j;
		}
		++i;
	}
	return (0);
}


int	visit_residual_nodes(t_path *data, int *current_path)
{
	int j;
	int i;
	t_hash *node;
	int *queue;
	int q_size;

	i = 0;
	queue = q_get_list();
	q_size = q_get_len();

	while (i < q_size)
	{
		j = 0;
		node = data->room_list[queue[i]];
		while (node->links[j])
		{
			if (!current_path[node->links[j]->id]
				&& node->links[j]->id != data->start->id)
			{
				current_path[node->links[j]->id] = queue[i];
				if (end_has_been_reached(data, data->room_list[node->links[j]->id]))
				{
					free(queue);
					return (1);
				}
				q_enqueue(node->links[j]->id);
			}
			++j;
		}
		q_pop(queue[i]);
		++i;
	}
	free(queue);
	return (0);
}



int	bad_bfs(t_path *data)
{
	q_add_queue(data->room_count);
	q_enqueue(data->start->id);
	while (!q_is_empty())
	{
		if (visit_non_residual_nodes(data, data->current_paths, data->residue))
		{
			bfs_trash_collector(data, data->current_paths);
			return (1);
		}
		if (visit_residual_nodes(data, data->current_paths))
		{
			bfs_trash_collector(data, data->current_paths);
			return (1);
		}
	}
	return (0);
}

int is_equal(int *array, int *array2, int size)
{

	int i;
	i = 0;

	if(!array || !array2 || !size)
		return (0);

	while(size--)
	{
		if (array[i] != array2[i])
			return (0);
		++i;
	}
	return(1);
}

void allocate_memory_for_bfs(t_path *data)
{
	data->start = data->room_list[data->start_id];
	data->end = data->room_list[data->end_id];
	data->winner_turns = -1;
	data->winner = (int *)ft_memalloc(sizeof(int) * data->room_count);
	data->current_paths = (int *)ft_memalloc(sizeof(int) * data->room_count);
	data->residue = (int *)ft_memalloc(sizeof(int) * data->room_count);
	data->first_full_set = (int *)ft_memalloc(sizeof(int) * data->room_count);
	if (!data->winner || !data->current_paths || !data->residue || !data->first_full_set)
		exit(1);

	ft_memset(data->first_full_set, -1, sizeof(int) * data->room_count);
}

void do_stuff_to_paths(t_path *data)
{
	allocate_memory_for_bfs(data); // I put everything in the data struct residue winner first_full_set etc


	//while (!is_equal(data->current_paths, data->first_full_set, data->room_count)
	//	&& !is_equal(data->current_paths, data->winner, data->room_count))
	while(data->winner_turns == -1 // default value of winner_turns
		|| !is_equal(data->winner, data->current_paths, data->room_count))
	{
		while (bad_bfs(data))
		{
			print_data(data);
			get_winner(data);
		}

		ft_memcpy(data->residue, data->current_paths, sizeof(int) * data->room_count);
		ft_memset(data->current_paths, 0, sizeof(int) * data->room_count);
		//if (*data->first_full_set == -1) //first_round_as all ints in this array are first set as -1
		//	ft_memcpy(data->first_full_set, data->current_paths, sizeof(int) * data->room_count);

	}
}

int	main(void)
{
	t_path	data;

	q_init();
	ft_memset(&data, 0, sizeof(data));
	read_input(&data);
	do_stuff_to_paths(&data);
		//print_paths(&data);
		//march_ants(do_stuff_to_paths(data));
	hash_destroy();
	exit (666);
}
