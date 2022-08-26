/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/26 23:30:36 by akoykka          ###   ########.fr       */
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
	int start_cut;
	int end_cut;

	i = 0;
	min_cut_start = 0;
	while (i < data->room_count)
	{
		if ((data->adj_grid)[START][i])
			++min_cut_start;
		++i;
	}
	i = 0;
	min_cut_end = 0;
	while (i < data->room_count)
	{
		if ((data->adj_grid)[END][i])
			++min_cut_end;
		++i;
	}
	if (min_cut_end < min_cut_start)
		return (min_cut_end);
	return(min_cut_start);
}


void visit_neighbours(t_path *data, int current_node)
{
	int i;

	i = 0;
	while (ROOM_COUNT > i)
	{




	}

}

void mark_neighbours(t_path *data int current_node)
{
	int i;

	i = 0;
	while (ROOM_COUNT > i)
	{
		if (ADJ_GRID[current_node][i]
			&& !PREV_NODE[i])
			PREV_NODE[i] = current_node
	}
}

void fill_queue(t_path *data, int node, int depth)
{
	jos depth on kolme
	if !depth
		save node numbers on here
	while(depth--)
	{
		while()
			fill_queue(data, depth);

	}

}


int *visit_all_nodes(t_path *data, int *values);
{
	int i;
	int *new_queue;
	int q_size;

	new_queue = ft_memalloc(sizeof(int) * ROOM_COUNT);
	while(Q_SIZE)
	{
		while(i < ROOM_COUNT)
		{
			if (ADJ_GRID[value][i] == ADJACENT)
			{
			ADJ_GRID[value][i] = value;
			QUEUE[Q_SIZE] = i;
			Q_SIZE++;
			}
		}



}



void get_paths(t_path *data)
{
	int max_paths;

	max_paths = get_min_cut(data);
	maxpaths = ft_memalloc(max_paths);
	while(maxpaths reached || all path combinations tried)
	{
		visit_all_nodes()
		compare_paths()
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
	get_paths()
	march_ants()
	free_all()
	exit()




}