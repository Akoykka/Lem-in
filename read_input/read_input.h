/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:23:25 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/08 14:08:56 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_INPUT_H
# define READ_INPUT_H
# include "../lem_in.h"
# include "../libft/includes/get_next_line.h"
# define HASH_SIZE 207257
# define STDIN 0

typedef struct s_hash
{
	char *name;
	int xy[2];
	int number;
	t_hash **adj;
	int		adj_size;
}			t_hash;


void get_ants(t_path *data, char *str);
int array_len(char **array);
int	is_valid_room(char **room, int field_count);
void parse_room(t_path *data, char *str);
void make_grid(t_path *data);
void parse_link(t_path *data, char *str);
int is_cmd_or_comment(t_path *data, char *line);
void read_input(t_path *data);

void save_link(t_path *data, char *room_name, char *room2_name);
void save_room(t_path *data, char *room_name, int y, int x);
unsigned long get_room(t_path *data, char *str);
int search_name_list(t_path *data, char *room_name);
int hash_check_collision(t_path *data, unsigned long digest);
unsigned long hash(char *str);



#endif