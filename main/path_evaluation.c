/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_evaluation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:20:12 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 15:14:29 by akoykka          ###   ########.fr       */
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
	int path_ant_cap;

	path_ant_cap = turns->path_count * turns->longest_len - turns->total_len;

	if (ants - path_ant_cap <= 0)
		return(2147483647);
	if ((ants - path_ant_cap) % turns->path_count)
		return ((ants - path_ant_cap) / turns->path_count + 1 + turns->longest_len) ;
	return ((ants - path_ant_cap) / turns->path_count + turns->longest_len);
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
		if (ADJ_GRID[data->end][i] && paths[i])
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
	if (!data->best_path || turns < data->best_turn_count)
	{
		free(data->best_path);
		data->best_path = NULL;
		data->best_path = curr_path;
		data->best_turn_count = turns;
		data->path_changed = 1;
		return ;
	}
	free(curr_path);
	curr_path = NULL;
}
