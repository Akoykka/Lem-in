/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/14 20:01:31 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void parse_ants(t_path *data, char *str)
{
	int static ants_saved;

	if (ants_saved == 1)
		return;
	if (ft_isint(str))
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

void parse_room(t_path *data, char *line)
{
	static int	all_rooms_saved;
	char 		**info;

	if (all_rooms_saved)
		return ;
	info = ft_strsplit(line, ' ');
	if (ft_array_len(info) == 3 && ft_isint(info[1]) && ft_isint(info[2]))
	{
		hash_add(info[0], ft_atoi(info[1]), ft_atoi(info[2]), data->room_count);
		(data->room_list)[data->room_count] = ft_strdup(info[0]);
		data->room_count++;
	}
	else
		all_rooms_saved = 1;
	ft_free_array(info);
}

void parse_link(t_path *data, char *str)
{
	char **link;
	int room_num;
	int room_num2;

	if (!data->adj_grid)
		make_grid(data);
	link = ft_strsplit(str, '-');
	if (!link)
		exit(1);
	if (ft_array_len(link) == 2)
	{
		room_num = hash_get_number(link[0]);
		room_num2 = hash_get_number(link[1]);
		data->adj_grid[room_num][room_num2] = 1;
		data->adj_grid[room_num2][room_num] = 1;
	}
	ft_free_array(link);
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

void read_input(t_path *data)
{
	char	*line;
	int		ret;

	allocate_memory(data);
	line = NULL;
	ret = get_next_line(0, &line);
	while (ret)
	{
		if (ret == -1)
			exit(-1);
		if (!is_cmd_or_comment(data, line))
		{
			parse_ants(data, line);
			parse_room(data, line);
			parse_link(data, line);
		}
		free(line);
		line = NULL;
		ret = get_next_line(0, &line);
	}
	hash_destroy();
}
