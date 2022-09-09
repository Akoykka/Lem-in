/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/09 19:18:30 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"

void parse_ants(t_path *data, char *str)
{
	int static ants_saved;

	if (ants_saved == 1)
		return;
	if (ft_is_int(str))
	{
		data->ant_count = ft_atoi(str);
		ants_saved = 1;
	}
	else
	{
		printf("ERROR ANTS");
		exit (1);
	}
}

int array_len(char **array)
{
	int i;

	i = 0;
	while(array && array[i])
		++i;
	return(i);
}

int	is_valid_room(char **room, int field_count)
{
	if (field_count == 3 && ft_is_int(room[1]) && ft_is_int(room[2]))
			return (1);
	return (0);
}

void parse_room(t_path *data, t_table *t, char *room_data)
{
	static int	rooms_saved;
	char 		**fields;

	if (rooms_saved == 1)
		return ;
	fields = ft_strsplit(room_data, ' ');
	if (is_valid_room(fields, array_len(fields)))
		{
			save_room(data, t, fields);
			data->room_count++;
		}
	else
		rooms_saved = 1;
	//free_array(fields);
}

void make_grid(t_path *data)
{
	int i;
	i = 0;

	data->adj_grid = (int **)ft_memalloc(sizeof(int *) * data->room_count);
	if (!data->adj_grid)
		exit(1);
	while(data->room_count > i)
	{
		(data->adj_grid)[i] = (int *)ft_memalloc(sizeof(int) * data->room_count);
		if (!(data->adj_grid)[i])
			exit(1);
		++i;
	}
}

int is_valid_link(t_path *data, char **rooms, int field_count)
{
	if (field_count != 2)
		return (0);
	if (data->hash_table[hash(rooms[0])])


}

void parse_link(t_path *data, t_table *t, char *str)
{
	char **link_names;

	if (!data->adj_grid)
		make_grid(data);
	link_names = ft_strsplit(str, '-');
	if (!link_names)
		exit(1);
	if (is_valid_link(link_names, array_len(link_names)))
		save_link(data->adj_grid, t ,link_names[0], link_names[1]);
	else
	{
		printf("Error savelink\n");
		exit(1);
	}
	//free_array(link_names);
}

int is_cmd_or_comment(t_path *data, char *line)
{
	static int start_found;
	static int end_found;

	if(line[0] == '#')
	{
		if(!ft_strcmp(line, "##start"))
		{
				data->start = data->room_count;
				start_found += 1;
		}

		if (!ft_strcmp(line, "##end"))
		{
				data->end = data->room_count;
				end_found += 1;
		}
	}
	if (line[0] == 'L' ||( line[0] == '#' && line[1] == '#')
		|| start_found == 2 || end_found == 2)
		exit(1);
	return (1);
}

void init_hash_table(t_table *t)
{
	char *line;
	int total_lines;
	
	line = NULL;
	total_lines = 0;
	ft_memset(t, 0, sizeof(t_table));
	while (get_next_line(STDIN, &line))
	{
		free(line);
		line = NULL;
		++total_lines;
	}
	t->table = (t_hash *)ft_memalloc(sizeof(t_hash) * (total_lines * 3));
	if (!t->table)
		exit(1);
	t->table_size = total_lines * 3;
}

/*
void destroy_table(t_table *t)
{
	int i;

	i = 0;
	while (t->table_size > i)
	{
		if ((t->table)[i])
			free(((t->table)[i])->name);
		free((t->table)[i]);
	}
	free(t->table);
	t->table = NULL
}
*/

void read_input(t_path *data)
{
	t_table	t;
	char	*line;
	int		ret;

	init_hash_table(&t);	
	line = NULL;
	ret = get_next_line(STDIN, &line);
	while (ret)
	{
		if (ret == -1)
			exit(-1);
		if (!is_cmd_or_comment(data, line))
		{
			parse_ants(data, line);
			parse_room(data, &t, line);
			parse_link(data, &t, line);
		}
		free(line);
		line = NULL;
		ret = get_next_line(STDIN, &line);
	}
	//destroy_table();
}
