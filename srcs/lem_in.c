/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/10/03 18:09:50 by akoykka          ###   ########.fr       */
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
	if (ants - ant_leak <= 0) // Something like this
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

	i = 1;
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

int	get_winner(t_path *data, int *winner, int winner_turns, int *current_path)
{
	int	turns;

	turns = calc_turns(data, current_path);
	//printf("-------------------\n Paths are:\n");
	//print_real_paths(data, current_path);
	//printf("-------------------\n");
	//printf("\nturns: %i\n\n", turns);
	if (turns < winner_turns)
		ft_memmove(winner, current_path, sizeof(int) * data->room_count);
	return(winner_turns);
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

void	save_result(t_path *data, int *first_result, int *current_paths)
{
	first_result = (int *)ft_memalloc(sizeof(int) * data->room_count);
	if (!first_result)
	{
		ft_memcpy(first_result, current_paths, sizeof(int) * data->room_count);
		exit(1);
	}
}



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



int	bad_bfs(t_path *data, int *current_paths, int *residue)
{
	q_add_queue(data->room_count);
	q_enqueue(data->start->id);
	while (!q_is_empty())
	{
		if (visit_non_residual_nodes(data, current_paths, residue))
			return (1);
		if (visit_residual_nodes(data, current_paths))
			return (1);
	}
	return (0);
}

int is_equal(int *array, int *array2, int size)
{
	int i;
	i = 0;
	while(size--)
	{
		if (array[i] != array2[i])
			return (0);
		++i;
	}
	return(1);
}


int	*do_stuff_to_paths(t_path *data)
{
	int	*winner;
	int winner_turns;
	int *residue;
	int	*current_paths;
	int	*first_full_set;

	winner_turns = 99999999; /// Work on this.
	winner = (int *)ft_memalloc(sizeof(int) * data->room_count);
	current_paths = (int *)ft_memalloc(sizeof(int) * data->room_count);
	residue = (int *)ft_memalloc(sizeof(int) * data->room_count);



	if (!winner || !current_paths || !residue)
		exit(1);
	first_full_set = NULL;
	while (first_full_set == NULL
		|| (!is_equal(current_paths, first_full_set, data->room_count)
		&& !is_equal(current_paths, winner, data->room_count)))
	{
		while (bad_bfs(data, current_paths, residue))
			bfs_trash_collector(data, current_paths);
		bfs_trash_collector(data, current_paths);
		winner_turns = get_winner(data, winner, winner_turns, current_paths);
		if (first_full_set == NULL)
			save_result(data, first_full_set, current_paths);
		ft_memcpy(residue, current_paths, sizeof(int) * data->room_count);
		ft_memset(current_paths, 0, sizeof(int) * data->room_count);
	}
	free(first_full_set);
	free(current_paths);
	return (winner);
}

int	main(void)
{
	t_path	data;
	int		*winner;

	q_init();
	ft_memset(&data, 0, sizeof(data));
	read_input(&data);
	data.start = data.room_list[data.start_id];
	data.end = data.room_list[data.end_id];
	winner = do_stuff_to_paths(&data);
		//print_paths(&data);
		//march_ants(do_stuff_to_paths(data));
	hash_destroy();
	exit (666);
}
