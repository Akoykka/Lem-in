/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/13 19:17:37 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../hash/hash.h"
# include "../queue/queue.h"

# define ADJACENT 1
# define START 0
# define END 1
# define ADJ_GRID (data->adj_grid)
# define ROOM_COUNT (data->room_count)
# define COLLISION < 0

# include <stdio.h>

typedef struct s_path
{
	char	**room_list;
	int		**adj_grid;
	int		ant_count;
	int		room_count;
	int		start;
	int		end;

	int		*best_path;
	int		path_changed;
}				t_path;

typedef struct s_turns
{
	int total_len;
	int longest_len;
	int path_count;
}			t_turns;



/// READ INPUT 
void			read_input(t_path *data);
int				is_cmd_or_comment(t_path *data, char *line);
void 			parse_link(t_path *data, char *str);
void 			parse_room(t_path *data, char *line);
void 			parse_ants(t_path *data, char *str);

/// READ INPUT UTILS
unsigned int	count_input_lines(void);
void			make_grid(t_path *data);
void			allocate_memory(t_path *data);





/// PATH EVALUATION
int pathlen(int *paths, int node);
int get_turn_count(int ants, t_turns *turns);
int calc_turns(t_path *data, int *paths);
int get_winner(t_path *data, int **best, int *contender);

///QUEUE

void queue_add_end_neighbours(t_path *data, char *paths, t_queue *q);
void queue_empty_start_neighbours(t_path *data, t_queue *q);
void queue_remove_collision(int collision, t_queue *q);
void queue_add_adjacent(t_path *data, int *paths, t_queue *q);
#endif