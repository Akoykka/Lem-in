/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/07 14:38:39 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"


# define LEM_IN_H
# define ADJACENT 1
# define START 0
# define END 1
# define ADJ_GRID (data->adj_grid)
# define ROOM_COUNT (data->room_count)
# define COLLISION < 0
# define STDIN 0
# define HASH_SIZE 207257

typedef struct s_path
{
	char	name_list[HASH_SIZE];
	int		**adj_grid;
	int		ant_count;
	int		room_count;
	
	int		*best_path;
	int		path_changed;
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

/// Ft_is_int
int ft_is_int(char *str);


/// PATH EVALUATION
int pathlen(int *paths, int node);
int get_turn_count(int ants, t_turns *turns);
int calc_turns(t_path *data, int *paths);
int get_winner(t_path *data, int **best, int *contender);

///QUEUE
void queue_remove_head(t_queue *q);
void queue_add_room(t_queue *q, int room_number);
void queue_add_end_neighbours(t_path *data, char *paths, t_queue *q);
void queue_empty_start_neighbours(t_path *data, t_queue *q);
void queue_remove_collision(int collision, t_queue *q);
void queue_add_adjacent(t_path *data, int *paths, t_queue *q);
#endif