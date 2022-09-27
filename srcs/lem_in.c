/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/27 18:39:59 by akoykka          ###   ########.fr       */
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
	printf("-------------------\n Paths are:\n");
	print_real_paths(data, current_path);
	printf("-------------------\n");
	printf("\nturns: %i\n\n", turns);
	if (turns < winner_turns)
		ft_memmove(winner, current_path, sizeof(int) * data->room_count);
	return(winner_turns);
}

void	remove_residue(t_path *data, int *paths)
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

void store_n_add_to_prev_q(t_path *data, int *add_to_queue, int indicator)
{
	int i;

	i = 0;
	if (indicator == 1)
		return ;

	if (indicator == 0)
	{
	
	}

	if (indicator == 666)
	{
		while(add_to_queue[i])
		{	
			q_enqueue(*add_to_queue);
			++add_to_queue;
			
		}
		free(add_to_queue)
	}	

}


void	visit_non_residual_nodes(t_path *data, int *current_paths, int start)
{
	int i;
	int linked_node;
	int next_found;
	int add_to_queue;

	add_to_queue = NULL;
	i = 0;
	q_add_queue(data->room_count);
	q_enqueue(start);
	while(!q_is_empty)
	{	
		next_found = 0;
		while (data->room_list[q_peek()]->links[i])
		{
			linked_node = data->room_list[q_peek()]->links[i];
			if (current_paths[linked_node] == 0)
			{
				current_paths[linked_node] = q_peek();
				q_enqueue(linked_node);
				next_found = 1;
			}
			++i;
		}
		store_n_add_to_prev_q(&add_to_queue, next_found);
		q_dequeue();
	}
	q_delete_queue();
	store_n_add_to_prev_q(&add_to_queue, 666); // I dont know how to tdo this/
}


void visit_residual_nodes(t_path *data, int *current_path)
{
	int i;
	int linked_node;

	i = 0;
	while(!q_is_empty)
	{
		while (data->room_list[q_peek()]->links[i])
		{
			linked_node = data->room_list[q_peek()]->links[i];
			if (current_path[linked_node] < 0)
			{
				q_enqueue(linked_node);
				current_path[linked_node] = q_peek();
			}
			++i;
		}
		q_dequeue();
	}
}

void	bad_bfs(t_path *data, int *current_paths)
{
	q_add_queue(data->room_count);
	q_enqueue(data->start->id);
	while (!q_is_empty() || has_end_been_reached())
	{
		visit_non_residual_nodes(data, current_paths, q_peek());
		visit_residual_nodes(data, current_paths);
	}
		
}

int	*do_stuff_to_paths(t_path *data)
{
	int	*winner;
	int winner_turns;
	int	*current_paths;
	int	*first_full_set;

	winner_turns = 99999999; /// Work on this.
	winner = (int *)ft_memalloc(sizeof(int) * data->room_count);
	current_paths = (int *)ft_memalloc(sizeof(int) * data->room_count);
	if (!winner || !current_paths)
		exit(1);
	first_full_set = NULL;
	while (first_full_set == NULL || current_paths != first_full_set || current_paths != winner)
	{
		bad_bfs(data, current_paths);
		remove_residue(data, current_paths);
		winner_turns = get_winner(data, winner, winner_turns, current_paths);
		if (first_full_set == NULL)
			save_result(data, first_full_set, current_paths);
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
	winner = do_stuff_to_paths(&data);
		//print_paths(&data);
		//march_ants(do_stuff_to_paths(data));
	hash_destroy();
	exit (666);
}
