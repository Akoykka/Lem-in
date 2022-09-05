/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_evaluation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:20:12 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/05 17:08:02 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "lem_in.h"


int pathlen(int *paths, int node)
{
	int len;

	len = 0;
	while (node != START)
	{
		node = paths[node];
		++len;
	}
	return (len);

}

int get_turn_count(int ants, t_turns *turns)
{
	int ant_cap;

	ant_cap = turns->path_count * turns->longest_len - turns->total_len;

	if (ants - ant_cap <= 0)
		return(calc_small_ant_amount_turn_count);
	if ((ants - ant_cap) % turns->path_count)
		return ((ants - ant_cap) / turns->path_count + 1) ;
	return ((ants - ant_cap) / turns->path_count);
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
		if (ADJ_GRID[END][i] && paths[i])
		{
			path_len = pathlen(paths, i);
			if (path_len > turn_count.longest_len)
				turn_count.longest_len = path_len;
			turn_count.total_len += path_len;
			++turn_count.path_count;
		}
		++i;
	}
	return(get_turn_count(data->ant_count, &turn_count));
}


int get_winner(t_path *data, int **best, int *curr_path)
{
	if (!*best || calc_turns(data, curr_path) < calc_turns(data, *best))
	{
		free(*best);
		*best = curr_path;
		return (1);
	}
	free(curr_path);
	curr_path = NULL;
	return (0);
}
