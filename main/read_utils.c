/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:19:27 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/20 13:44:34 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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


t_list *allocate_memory(t_path *data)
{
	t_list *fock;
	int ret;
	char *line;
	t_list *new;
	
	fock = NULL;
	ret = get_next_line(0, &line);
	if (ret == -1)
		exit(1);
	
	while (ret)
	{
		if (ret == -1)
			exit(1);
		new = ft_lst_new(line, sizeof(char) * ft_strlen(line));
		if (!new)
			exit(1);
		ft_lst_add(&fock, new);
		ret = get_next_line(0, &line);
	}
	hash_init(ft_lst_count(fock) * 7);
	data->room_list = (char **)ft_memalloc(sizeof(char *) * ft_lst_count(fock));
	if (!data->room_list)
		exit(1);
	data->room_list[0] = ft_memalloc(sizeof(char) * ft_lst_count(fock));
	data->room_count = 1;
	ft_lst_reverse(&fock);
	return(fock);
}