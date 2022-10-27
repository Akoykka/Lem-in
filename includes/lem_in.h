/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/10/27 09:37:27 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include "queue.h"

typedef struct s_hash
{
	int				id;
	char			*name;
	int				xy[2];
	struct s_hash	*parent;
	struct s_hash	**links;
	int				link_size;
}			t_hash;

typedef struct s_path
{
	int				ant_count;
	int				room_count;
	int				start_id;
	int				end_id;
	int				*visit;
	t_hash			*start;
	t_hash			*end;
	t_hash			**room_list;
	t_hash			**hash_table;
	unsigned long	table_size;
	int				*edges;
	int				*flow;
	int				*winner;
	int				winner_turns;
}				t_path;

// HASH
void			hash_add(t_path *data, char *name, int x, int y);
unsigned long	hash_djb2(char *key);
t_hash			*hash_get(t_path *data, char *key);

// READ INPUT
int				is_valid_input(char *line);
char			**read_input(t_path *data);
int				is_cmd_or_comment(t_path *data, char *line);
void			hash_add_link(t_path *data, char *key1, char *key2);
void			add_link_to_node(t_hash **dst, t_hash **src, int size);
void			parse_link(t_path *data, char *str);
int				parse_room(t_path *data, char *line);
int				parse_ants(t_path *data, char *str);
char			*get_stdin_input(void);
char			*memory_realloc(char *src, char *src2);
int				read_stdin(char *buf);
char			**allocate_memory(t_path *data);
void			print_array(char **array);

// AUGMENT_PATHS(BFS) PREPARATION
void			allocate_memory_for_bfs(t_path *data);
void			reset_values(t_path *data);
void			free_all(t_path *data, char **input);
int				start_is_next_to_end(t_path *data);
void			move_all_ants(t_path *data, char **input);

// AUGMENT PATHS
int				augment_paths(t_path *data);
void			visit_adj_nodes(t_path *data, int node);
int				is_flow(t_path *data, int node);
int				is_edge(t_path *data, int node);
void			visit(t_path *data, int node);

// RULES.C FOR BFS
void			apply_rules(t_path *data, int current, int adj_node);
void			appoint_parent(t_path *data, int current, int adj_node);
int				against_flow(t_path *data, int current, int adj_node);
int				inside_flow(t_path *data, int current, int adj_node);
int				break_flow(t_path *data, int current, int adj_node);

// ALTER FLOW
void			alter_flow(t_path *data);
int				traverse_flow(t_path *data, int node);
int				backtrack_and_delete_flow(t_path *data, int node);

// EVALUATION
typedef struct s_turns
{
	int			total_len;
	int			longest_len;
	int			path_count;
}				t_turns;

int				pathlen(int *paths, int node, int start);
int				get_turn_count(int ants, t_turns *turns);
int				calc_turns(t_path *data, int *paths);
void			compare_paths(t_path *data);

// ERROR HANDLING 
void			print_usage(void);
void			check_validity(t_path *data, char **lines);
void			error(char *error_msg, int exit_code);

// PRINT OUTPUT
typedef struct s_print
{
	t_hash	**room_list;
	t_hash	*end;
	t_hash	*start;
	int		ants_left;
	int		*ant;
	int		*paths;
	char	*moves;
	int		moves_len;
	int		moves_size;
	int		path_count;
}				t_print;


void	print_answer(t_path *data, char **input);
void 	prepare_print(t_path *data, t_print *print);
void	strcat_one_line(t_print *print);
void 	strcat_path(t_print *print, int curr_path);
void	strcat_new_ant(t_print *print, int dest);
void	strcat_move(t_print *print, int ant_num, int dest);
void 	realloc_check(t_print *print, int ant_num, int dest);

#endif