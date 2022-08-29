/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/29 09:33:29 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "lem_in.h"

int	is_only_numbers(char *str)
{
	if (*str == '-' && ft_strlen(str) > 1)
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

int	is_bigger_than_max(char *str)
{
	if (ft_isdigit(*str))
	{
		if (ft_strlen(str) > 10 || (ft_strlen(str) == 10
				&& ft_strcmp(str, "2147483647") > 0))
			return (1);
	}
	return (0);
}

int	is_smaller_than_min(char *str)
{
	if (*str == '-')
	{
		if (ft_strlen(str) > 11 || (ft_strlen(str) == 11
				&& ft_strcmp(str, "-2147483648") > 0))
			return (1);
	}
	return (0);
}

int	is_valid_room(char **room, int field_count)
{
	if (field_count != 3)
		return (0);
	if (!is_only_numbers(input[1])
		|| is_bigger_than_max(input[1])
		|| is_smaller_than_min(input[1])
			return (0);
	if (!is_only_numbers(input[2])
		|| is_bigger_than_max(input[2])
		|| is_smaller_than_min(input[2])
			return (0);
	return (1);
}

int count_fields(char **array)
{
	int i;

	i = 0;
	while(array && array[i])
		++i;
	return(i);
}

void save_room_name(t_path *data, char *new_room)
{
	int i;
	int curr_field_count;
	char **new_list;

	i = 0;
	curr_field_count = count_fields(data->name_list);
	new_list(char **)ft_memalloc(sizeof(char *) * curr_field_count + 2);

	//if(new_list)
		//exit_procedure(data)

	while (curr_field_count > i)
	{
		(data->name_list)[i] = newlist[i];
		++i;
	}
	newlist[i] = new_room;
	newlist[i + 1] = NULL;
}


void save_valid_rooms(t_path *data, int argc, char **argv)
{
	char	**line;
	int		i;

	i = 0;
	while(argc > i)
	{
		line = ft_strsplit(argv[i])
		//if (!line)
		// exit_procedure;
		if (line[0] && line[0] != '#' && line[0] != 'L'
			&& is_valid_room(line, count_fields(line)))
			save_room_name(data, line[0])
		//free_array(line);
		//line = NULL;
		++i;
	}
	data->room_count = count_fields(data->name_list);
	set_start();
	set_end();
}

void make_grid(t_path *data)
{
	int i;
	i = 0;

	data->adjacency = (int **)ft_memalloc(sizeof(int *) * data->room_count);
	// if data->adjancency
	//	exit_procedure()
	while(room_count > i)
	{
		(data->adjacency)[i] = (int *)ft_memalloc(sizeof(int) * data->room_count);
		//if (data->adjacency)[i]
		//	exit_procedure()
		++i;
	}
}

int is_valid_link(t_path *data, char **line int field_count)
{
	int node_found;
	int node2_found;
	int i;

	node_found = 0
	node2_found = 0;
	i = 0;
	if (field_count != 2)
		return (0);
	while((data->name_list)[i])
	{
		if (!ft_strcmp(line[0], (data->name_list)[i]))
			node_found = 1;
		if (!ft_strcmp(line[1], (data->name_list)[i]))
			node2_found = 1;
		i++;
	}
	if (node_found && node2_found)
		return (1);
	return (0);
}

void mark_to_grid(t_path *data, char *node1, char *node2)
{
	int node_id;
	int node_id2;
	int i;

	i = 0;
	while((data->name_list)[i])
	{
		if (!ft_strcmp(node1, (data->name_list)[i]))
			node1_id = i;
		if (!ft_strcmp(node2, (data->name_list)[i]))
			node2_id = i;
		i++;
	}
	(data->adj_grid)[node1_id][node2_id] = 1;
	(data->adj_grid)[node2_id][node1_id] = 1;
}

void save_valid_links(t_path *data, int argc, char **argv)
{
	int i;
	char **line;

	line = NULL;
	i = 0;
	make_adj_grid(data);
	while(argc > i)
	{
		if(argv[i] != '#')
		{
			line = ft_strsplit(argv[1], '-');
			//if (!line)
			// exit_procedure()
			if (is_valid_link(data, line, count_fields(line))
				mark_to_grid(data, line[0], line[1]);
			///free_array()
		}
	}
}

int get_min_cut(data)
{
	int i;
	int min_cut_start;
	int min_cut_sink;

	i = 0;
	min_cut_start = 0;
	min_cut_sink = 0;
	while (i < ROOM_COUNT)
	{
		if (ADJ_GRID[START][i])
			++min_cut_start;
		++i;
	}
	i = 0;
	while (i < ROOM_COUNT)
	{
		if (ADJ_GRID[SINK][i])
			++min_cut_sink;
		++i;
	}
	if (min_cut_sink < min_cut_start)
		return (min_cut_sink);
	return(min_cut_start);
}

int is_adjacent(t_path *data, int room, int room2)
{
	if (ADJ_GRID[room][room2] == ADJACENT)
		return (1);
	return (0);
}

void visit(t_path *data, int room, int prev_room)
{
	if (room != START || room != SINK)
		ADJ_GRID[room][prev_room] = prev_room;
}

void queue_add(data, room_number)
{
	QUEUE[Q_SIZE] = room_number;
	Q_SIZE++;
}

void queue_remove_head(t_path *data)
{
	ft_memmove(&QUEUE[1], QUEUE, sizeof(int) * Q_SIZE);
	Q_SIZE--;
}

/*
// Looks up all nodes in BFS and marks previous on
// the adjacecency_grid . Is_adjacent also checkes
// has node been visited already;
*/
void visit_all_nodes(t_path *data)
{
	int i;
	int room_number;
	t_queue queue;

	i = 0;
	Q_SIZE = 1;
	QUEUE = (int *)ft_memalloc(sizeof(int) * ROOM_COUNT + 1);
	//if (!QUEUE)
	//	exit_procedure();
	while(Q_SIZE)
	{
		room_number = 0;
		while(ROOM_COUNT > room_number)
		{
			if (is_adjacent(data, room_number, QUEUE[i])
			{
				if (room_number == SINK)
					break ;
				visit(data, room_number, QUEUE[i]);
				queue_add(data, room_number)
			}
			++room_number;
		}
		queue_remove_head(data);
		++i;
	}
}

if adjacency_grids value is 0 or above, node has been visited and
set to previous nodes values which will lead back to start
see if there is previous numbers next to sink go check sinks
	adjacent vertices for previous is_only_numbers

void save_paths(t_path *data)
{
	while(ROOM_COUNT > i)
	{
		if (is_adjacent(data, SINK, i)
			&& ADJ_GRID[i][SINK] <= 0)
		{

		}
	}

}

void get_paths(t_path *data, int antcount)
{
	PATHS = ft_memalloc(sizeof(int *) * get_min_cut(data));
	while(maxpaths reached || all path combinations tried)
	{
		visit_all_nodes()
		save_paths(data)
		make_one_path_available()
	}

}

int main(int argc, char **argv)
{
	t_path data;

	argc -= 1;
	argv += 1;
	save_valid_rooms(&data, argc, argv);
	save_valid_links(&data, argc, argv);
	trim_nodes(&data) /// destroy nodes with only one neighbour
	get_paths(&data)
	march_ants()
	free_all()
	exit()




}