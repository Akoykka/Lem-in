/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:48 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/27 18:40:02 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	parse_ants(t_path *data, char *str)
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

int	parse_room(t_path *data, char *line)
{
	char	**info;

	info = ft_strsplit(line, ' ');
	if (ft_array_len(info) == 3 && ft_isint(info[1]) && ft_isint(info[2]))
	{
		hash_add(info[0], ft_atoi(info[1]), ft_atoi(info[2]), data);
		data->room_count++;
		ft_free_array(info);
	}
	else
	{
		parse_link(line);
		return (2);
	}
	return (1);
}

void	hash_add_link(char *node1, char *node2)
{
	t_hash	*room1;
	t_hash	*room2;
	int		i;

	i = 0;
	room1 = hash_get(node1);
	room2 = hash_get(node2);
	while (room1->links[i])
		i++;
	room1->links[i] = room2;
	i = 0;
	while (room2->links[i])
		i++;
	room2->links[i] = room1;
}

void	parse_link(char *str)
{
	char	**link;

	link = ft_strsplit(str, '-');
	if (!link)
		exit (1);
	if (ft_array_len(link) == 2)
	{
		hash_add_link(link[0], link[1]);
	}
	ft_free_array(link);
}

int	is_cmd_or_comment(t_path *data, char *line)
{
	static int	start_found;
	static int	end_found;

	if (line[0] == '#')
	{
		if (!ft_strcmp(line, "##start"))
		{
				data->start = data->room_count;
				start_found += 1;
		}
		if (!ft_strcmp(line, "##end"))
		{
				data->end = data->room_count;
				end_found += 1;
		}
		return (1);
	}
	if (line[0] == 'L' ||( line[0] == '#' && line[1] == '#') || start_found == 2 || end_found == 2)
		exit (1);
	return (0);
}

void	read_input(t_path *data)
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
			if (stage == 2)
				parse_link(lines[i]);
			if (stage == 1)
				stage = parse_room(data, lines[i]);
			if (stage == 0)
				stage = parse_ants(data, lines[i]);
		}
		++i;
	}
}
