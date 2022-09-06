/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/06 18:56:11 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define ADJACENT 1
# define START 0
# define END 1
# define ADJ_GRID (data->adj_grid)
# define ROOM_COUNT (data->room_count)
# define COLLISION < 0

typedef struct s_path
{
	int		ant_count;
	int		room_count;
	char	**name_list;
	
	int		**adj_grid;
	int		*best_path;
}				t_path;

typedef struct s_queue
{
	int		*queue;
	int		size;
}			t_queue;

typedef struct s_turns
{
	int total_len;
	int longest_len;
	int path_count;
}			t_turns;

/// PATH EVALUATION
int pathlen(int *paths, int node);
int get_turn_count(int ants, t_turns *turns);
int calc_turns(t_path *data, int *paths);
int get_winner(t_path *data, int **best, int *contender);


#endif