/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:23:25 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/10 09:50:43 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_INPUT_H
# define READ_INPUT_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# define HASH_SIZE 207257
# define STDIN 0
# include <stdio.h>
typedef struct s_path
{
	t_list *room_list;
	int		**adj_grid;
	int		ant_count;
	int		room_count;
	int		start;
	int		end;

	int		*best_path;
	int		path_changed;
}				t_path;

typedef struct s_hash
{
	char *name;
	int xy[2];
	int number;
}			t_hash;

typedef struct s_table
{
	t_hash			*table;
	unsigned long	table_size;
}			t_table;




void init_hash_table(t_table *t);
void read_input(t_path *data);
void parse_room(t_path *data, t_table *t, char *room_data);


unsigned long hash(char *str);
void save_link(t_path *data, t_table *t, char *room_name, char *room2_name);
int get_room_number(t_table *t, char *room_name);
void save_room(t_path *data, t_table *t, char **room_data);
int hash_add(t_table *t, unsigned long digest, char **room_data, int room_number);
#endif