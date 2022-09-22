/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_evaluation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:20:12 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 18:54:34 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int pathlen(int *paths, int node, int start)
{
	int len;

	len = 0;
	while (node != start)
	{
		node = paths[node];
		++len;
	}
	return (len);

}

int get_turn_count(int ants, t_turns *turns)
{
	int ant_leak;

	ant_leak = turns->path_count * turns->longest_len - turns->total_len;

	if (ants - ant_leak <= 0)
		return(2147483647);
	if ((ants - ant_leak) % turns->path_count)
		return ((ants - ant_leak) / turns->path_count + 1 + turns->longest_len);
	return ((ants - ant_leak) / turns->path_count + turns->longest_len);
}


int calc_turns(t_path *data, int *paths)
{
	int i;
	int path_len;
	t_turns turn_count;

	i = 0;
	ft_memset(&turn_count, 0, sizeof(t_turns));
	while(data->room_count > i)
	{
		if (data->adj_grid[data->end][i] && paths[i])
		{
			path_len = pathlen(paths, i, data->start);
			if (path_len > turn_count.longest_len)
				turn_count.longest_len = path_len;
			turn_count.total_len += path_len;
			++turn_count.path_count;
		}
		++i;
	}
	return(get_turn_count(data->ant_count, &turn_count));
}

void get_winner(t_path *data , int *curr_path)
{
	int turns;

	turns = calc_turns(data, curr_path);
	printf("-------------------\n Paths are:\n");
	print_real_paths(data, curr_path);
	printf("-------------------\n");
	printf("\nturns: %i\n\n", turns);
	if (turns < data->best_turn_count)
	{
		ft_memmove(data->best_path, curr_path, sizeof(int) * data->room_count);
		data->best_turn_count = turns;
	}
}

