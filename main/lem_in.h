/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/20 09:41:51 by akoykka          ###   ########.fr       */
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
	int		best_turn_count;
	int		path_changed;
}				t_path;

typedef struct s_turns
{
	int total_len;
	int longest_len;
	int path_count;
}			t_turns;

// DEBUG
void			q_print_queue();
void			print_int_array(int *arr, int size);

/// READ INPUT
void			read_input(t_path *data);
int				is_cmd_or_comment(t_path *data, char *line);
void 			parse_link(t_path *data, char *str);
int 			parse_room(t_path *data, char *line);
int 			parse_ants(t_path *data, char *str);

/// READ INPUT UTILS
unsigned int	count_input_lines(void);
void			make_grid(t_path *data);
t_list			*allocate_memory(t_path *data);


/// BFS
void 			q_unused_root_nodes(t_path *data);
void			q_add_adjacent(t_path *data, int *paths);
int				q_get_next_collision(void);
int				q_has_end(int end);
void			q_pop_collisions(t_path *data, int *paths);

void			bfs(t_path *data, int *paths, int root_node);
int				*dup_path(int *path, int size);


int		backtrack_collided_path(t_path *data, int *path, int collision);
void	set_latest_path_obstacle(t_path *data, int collision_point, int *paths);
void	get_paths(t_path *data);
void	visit_node(int node, int *path, int parent_room);
void	remove_obstacles(int *paths, int paths_size);
void	remove_residue(t_path *data, int *paths);
void	cpy_new_path(t_path *data, int *old_paths, int *new_paths, int end);

int		is_adjacent(t_path *data, int room);
int		is_obstacle(int *paths, int room);
int		is_collision(int node_number);
int		is_new_path(t_path *data, int *old_paths, int *new_paths, int end);
int 	is_end_path(t_path *data, int room, int *paths);
int		is_collision(int node_number);
int		is_obstacle(int *paths, int room);
int		is_adjacent(t_path *data, int room);


/// PATH EVALUATION
int		pathlen(int *paths, int node, int start);
int		get_turn_count(int ants, t_turns *turns);
int		calc_turns(t_path *data, int *paths);
void	get_winner(t_path *data, int *curr_path);



#endif