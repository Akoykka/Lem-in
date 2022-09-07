/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/07 15:27:11 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lem_in.h"
#include "stdio.h"

void get_ants(t_path *data, char *str)
{
	int static ants_saved;

	if (ants_saved = 1)
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
	if (field_count != 3 || !ft_is_int(room[1]) || !ft_is_int(room[2]))
			return (0);
	return (1);
}


void parse_room(t_path *data, char *str)
{
	static int rooms_saved;
	char **fields;
	
	if (rooms_saved)
		return ;
	fields = ft_strsplit(str, ' ');

	if (is_valid_room(fields, array_len(fields)))
		{
			save_room(data, fields[0], fields[1], fields[2]);
			data->room_count++;
		}
	else
		rooms_saved = 1;
	free_array(fields);
}

void parse_link(t_path *data, char *str)
{
	char **fields;

	if (!data->adj_grid)
		make_grid(data);
	fields = ft_strsplit(str, '-');
	if (!fields)
		exit(1);
		
	if (is_valid_link(fields, array_len(fields)))
		save_link(data->adj_grid, fields[0], fields[1]);
	else
	{
		printf("Error\n savelink");
		exit(1);
	}
	free_array(fields);
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
	if (line[0] == 'L' || line[0] == '#' && line[1] == '#'
		|| start_found == 2 || end_found == 2)
		exit(1);
	return (1);
}


void read_input(t_path *data)
{
	char	**line;
	int		ret;

	*line = NULL;
	ret = get_next_line(STDIN, line);
	while (ret)
	{
		if (ret = -1)
			exit(-1);
		if (!is_cmd_or_comment(data, *line))
		{
			parse_ants(data, *line);
			parse_room(data, *line);
			parse_link(data, *line);
		}
		free(*line);
		*line = NULL;
		ret = get_next_line(STDIN, line);
	}
}