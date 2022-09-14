/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/14 21:10:15 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../hash/hash.h"
# include "../queue/queue.h"

# define ADJ_GRID (data->adj_grid)
# define ROOM_COUNT (data->room_count)

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


/// BFS
void bfs(t_path *data, int *paths, int root_node);
int *dup_path(int *path, int size);
int is_adjacent(t_path *data, int room);
int is_obstacle(int *paths, int room);
int is_collision(int node_number);
void q_add_adjacent(t_path *data, int *paths);
int q_get_next_collision(void);
int backtrack_collided_path(t_path *data, int *path, int collision);
void set_latest_path_obstacle(t_path *data, int collision_point, int *paths);
void q_pop_collisions(t_path *data, int *paths);
int q_has_end(int end);

/// PATH EVALUATION
int pathlen(int *paths, int node);
int get_turn_count(int ants, t_turns *turns);
int calc_turns(t_path *data, int *paths);
int get_winner(t_path *data, int **best, int *contender);

#endif