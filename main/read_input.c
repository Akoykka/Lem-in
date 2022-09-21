/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 11:53:58 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int parse_ants(t_path *data, char *str)
{
	if (ft_isint(str))
	{
		data->ant_count = ft_atoi(str);
	}
	else
	{
		printf("ERROR ANTS");
		exit (1);
	}
	return (1);
}

int parse_room(t_path *data, char *line)
{
	char 		**info;

	info = ft_strsplit(line, ' ');
	if (ft_array_len(info) == 3 && ft_isint(info[1]) && ft_isint(info[2]))
	{
		hash_add(info[0], ft_atoi(info[1]), ft_atoi(info[2]), data->room_count);
		(data->room_list)[data->room_count] = ft_strdup(info[0]);
		data->room_count++;
		ft_free_array(info);
	}
	else
	{
		parse_link(data, line);
		return(2);
	}
	return(1);
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
		return(1);
	}
	if (line[0] == 'L' ||( line[0] == '#' && line[1] == '#')
		|| start_found == 2 || end_found == 2)
		exit(1);
	return (0);
}

void lst_behead(t_list **alst)
{
	t_list *behead;

	if (!alst)
		return;
	behead = *alst;
	*alst = (*alst)->next;
	free(behead->content);
	free(behead);
}


void read_input(t_path *data)
{
	char	**lines;
	int		stage;
	int		i;

	i = 0;
	stage = 0;
	lines = allocate_memory(data);
	while (lines[i])
	{
		if (!is_cmd_or_comment(data, lines[i]))
		{
			if(stage == 2)
				parse_link(data, lines[i]);
			if(stage == 1)
				stage = parse_room(data, lines[i]);
			if(stage == 0)
				stage = parse_ants(data, lines[i]);
		}
		++i;
	}
	hash_destroy();
}
