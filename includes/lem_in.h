/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/10/04 05:14:35 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/includes/libft.h"
# include "queue.h"

# define BUFF_SIZE 1000

# include <stdio.h>

typedef struct s_hash
{
	int id;
	char *name;
	int xy[2];
	struct s_hash *parent;
	struct s_hash **links;
	int	link_size;
}			t_hash;

typedef struct s_table
{
	t_hash			*table;
	unsigned long	table_size;
}			t_table;

typedef struct s_path
{
	int		ant_count;
	int		start_id;
	int		end_id;
	t_hash *start;
	t_hash *end;
	int		room_count;
	t_hash	**room_list;

	int		*first_full_set;
	int		*current_paths;
	int		*residue;

	int		*winner;
	int		winner_turns;
}				t_path;




// INIT
void 			hash_init(unsigned int table_size);
void			hash_destroy(void);

// FUNCTIONS
int				hash_get_number(char *name);
int				*hash_get_coords(char *name);
void			hash_add(char *name, int x, int y, t_path *data);

// STORAGE MANAGEMENT
unsigned long	hash_djb2(char *key);
t_hash			*hash_new(char *name, int x, int y, int number);
t_hash			*hash_get(char *name);
t_table			*hash_storage(void);

typedef struct s_turns
{
	int total_len;
	int longest_len;
	int path_count;
}			t_turns;

// DEBUG
void			q_print_queue(void);
void			print_int_array(int *arr, int size);

/// READ INPUT
void			read_input(t_path *data);
int				is_cmd_or_comment(t_path *data, char *line);
void 			parse_link(char *str);
int 			parse_room(t_path *data, char *line);
int 			parse_ants(t_path *data, char *str);

/// READ INPUT UTILS
unsigned int	count_input_lines(void);
char			**allocate_memory(t_path *data);


/// BFS
void			bfs(t_path *data, int *paths, int root_node);


/// PATH EVALUATION
int		pathlen(int *paths, int node, int start);
int		get_turn_count(int ants, t_turns *turns);
int		calc_turns(t_path *data, int *paths);
void	get_winner(t_path *data);


/// DEBUG FUNCTIONS DONT MIND

void print_data(t_path *data);
void ft_print_array(char **strings);
void ft_print_matrix(t_path *data);
void p_q(void);
void print_neigbours(t_path *data, int room);
void ft_print_matrix(t_path *data);
void queue_paths_in_print(t_path *data);
void hash_debug_print_table(void);
void print_real_paths(t_path *data, int *path);
void	print_one_path(t_path *data, int j, int *path);
void printq_room_names(t_path *data);
void print_int_array(int *arr, int size);
void p_p(t_path *data, int *paths);

#endif