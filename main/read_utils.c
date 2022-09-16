/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:19:27 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/16 19:07:57 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned int count_input_lines(void)
{
	char *line;
	unsigned int total_lines;

	line = NULL;
	total_lines = 0;
	while (get_next_line(0, &line) > 0)
	{
		//free(*line);
		//*line = NULL;
		printf("this is string %s\n", line);
		ft_strdel(&line);
		++total_lines;
	}
	return(total_lines);
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

void allocate_memory(t_path *data)
{
	unsigned int total_input_lines;

	total_input_lines = 10000;//count_input_lines();
	hash_init(total_input_lines * 3);
	data->room_list = (char **)ft_memalloc(sizeof(char *) * total_input_lines);
	if (!data->room_list)
		exit(1);
}