/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/28 16:39:35 by akoykka          ###   ########.fr       */
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
	if (ants - ant_leak <= 0) //// Something like this
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
		if (paths[(data->end->links[i])->id])
		{
			path_len = pathlen(paths, i, data->start->id);
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

void	bfs_trash_collector(t_path *data, int *paths)
{
	int	i;
	int	j;

	i = 0;
	while (data->end->links[i])
	{
		j = (data->end->links)[i]->id;
		while (paths[j] != data->start->id)
		{
			paths[j] *= -1;
			j = paths[j] * -1;
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

void	save_result(t_path *data, int *first_result, int *current_paths)
{
	first_result = (int *)ft_memalloc(sizeof(int) * data->room_count);
	if (!first_result)
	{
		ft_memcpy(first_result, current_paths, sizeof(int) * data->room_count);
		exit(1);
	}
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
	int *list;
	int list_size;
	int linked_node;
	int i;

	int j = 0;
	i = 0;
	list = q_get_list();
	list_size = q_get_len();
	while(list_size > i)
	{	
		j = 0;
		while(data->room_list[list[i]]->links[j])
		{
			
			linked_node = data->room_list[list[i]]->links[j]->id;
			if (!current_paths[linked_node] || !residue[linked_node] || linked_node != data->start_id)
			{
				q_add_queue(linked_node);
				current_paths[linked_node] = list[i];
				list[list_size] = linked_node;
				if (end_has_been_reached(data, data->room_list[linked_node]))
					return (1);
				list_size++;
				
			}
			j++;	
		}
		i++;
	}
	return (0);
}


int	visit_residual_nodes(t_path *data, int *current_path)
{
	int i;
	int linked_node;
	int *list;
	int list_size;
	int j;

	i = 0;
	list = q_get_list();
	list_size = q_get_len();
	while (list_size > i)
	{
		j = 0;
		while (data->room_list[list[i]]->links[j])
		{
			linked_node = data->room_list[list[i]]->links[j]->id;
			if (!current_path[linked_node] 
				|| current_path[linked_node] != data->start_id)
			{
				current_path[linked_node] = list[i];
				if (end_has_been_reached(data, data->room_list[linked_node]))
					return (1);
				q_add_queue(linked_node);
			}
			++j;
		}
		q_pop(list[i]);
		++i;
	}
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
	while (first_full_set == NULL || current_paths != first_full_set || current_paths != winner)
	{
		while(bad_bfs(data, current_paths, residue))
			bfs_trash_collector(data, current_paths);
		winner_turns = get_winner(data, winner, winner_turns, current_paths);
		if (first_full_set == NULL)
			save_result(data, first_full_set, current_paths);
		ft_memcpy(residue, current_paths, sizeof(int) * data->room_count);
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
		//ft_print_array(data.room_list);
		//ft_print_matrix(&data);
	data.start = data.room_list[data.start_id];
	data.end = data.room_list[data.end_id];
	winner = do_stuff_to_paths(&data);
		//print_paths(&data);
		//march_ants(do_stuff_to_paths(data));
	hash_destroy();
	exit (666);
}
