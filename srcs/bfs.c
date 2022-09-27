/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:16:03 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 18:42:58 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	get_turn_count(int ants, t_turns *turns)
{
	int	ant_leak;

	ant_leak = turns->path_count * turns->longest_len - turns->total_len;
	if (ants - ant_leak <= 0)
		return (2147483647);
	if ((ants - ant_leak) % turns->path_count)
		return ((ants - ant_leak) / turns->path_count + 1 + turns->longest_len);
	return ((ants - ant_leak) / turns->path_count + turns->longest_len);
}

int	evaluate_best_path(t_path *data) //NEED TO REMAKE WITH CURRENT PATHS INSTEAD OF PARENT
{
	t_hash	*temp;
	t_turns	turns;
	int		i;
	int		len;

	i = 0;
	turns.longest_len = -2147483648;
	turns.total_len = 0;
	while (data->end->links[i])
	{
		if (data->end->links[i]->parent)
		{
			turns.path_count++;
			len = 1;
			while (temp != data->start)
			{
				temp = hash_get(data->end->links[i]->parent);
				len++;
			}
			turns.total_len += len;
			if (turns.longest_len < len)
				turns.longest_len = len;
		}
		i++;
	}
	turns.path_count = i;
	return (get_turn_count(data->ant_count, &turns));
}

int	is_end(t_path *data, t_hash *current)
{
	int	i;

	i = 0;
	while (data->end->links[i])
	{
		if (current == data->end->links[i])
			return (1);
	}
	return (0);
}

void	add_neighbors(t_path *data, t_hash *current) //NEED TO REMAKE WITH CURRENT PATHS
{
	int	i;
	int	j;
	int	*best_path;

	i = 0;
	j = 0;
	while (current->links[i])
	{
		if (current->links[i]->visited == 0)
		{
			q_enqueue(current->links[i]->id);
			current->links[i]->visited = 1;
			current->links[i]->parent = current;
			if (is_end(data, current->links[i]))
				q_bzero();
		}
		++i;
	}
}

void	get_winner(t_path *data, int *winner, int *curr_path)
{
	int	*path;

	path = evaluate_best_path(data);
	if (path < data->best_turn_count)
	{
		data->best_turn_count = path;
		copy_best_path(data);
	}
}

void	bfs(t_path *data, int *paths, int root_node) //NEED TO CHANGE
{
	q_add_queue(data->room_count);
	q_enqueue(data->start->id);
	while (!q_is_empty())
	{
		add_neighbors(data, data->room_list[q_peek()]->id);
		q_dequeue();
	}
}
