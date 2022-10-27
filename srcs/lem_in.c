/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:22:05 by akoykka           #+#    #+#             */
/*   Updated: 2022/10/27 09:43:36 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	apply_rules(t_path *data, int current, int adj_node)
{
	if (!against_flow(data, current, adj_node))
	{
		if (break_flow(data, current, adj_node))
		{
			appoint_parent(data, current, adj_node);
			visit(data, data->flow[adj_node]);
			return ;
		}
		if (inside_flow(data, current, adj_node))
		{
			visit(data, adj_node);
			return ;
		}
		appoint_parent(data, current, adj_node);
		visit(data, adj_node);
	}
}

void	visit_adj_nodes(t_path *data, int node)
{
	int	i;
	int	adj_node;

	i = 0;
	
	while (data->room_list[node]->link_size > i)
	{
		adj_node = data->room_list[node]->links[i]->id;
		apply_rules(data, node, adj_node);
		++i;
	}
}

int	augment_paths(t_path *data)
{
	reset_values(data);
	while (!q_is_empty())
	{
		visit_adj_nodes(data, q_peek());
		q_dequeue();
		if (data->edges[data->end->id])
		{
			alter_flow(data);
			q_delete_queue();
			return (1);
		}
	}
	q_delete_queue();
	return (0);
}

int	main(void)
{
	t_path	*data;
	char	**input;

	data = (t_path *)ft_memalloc(sizeof(t_path));
	q_init();
	input = read_input(data);
	allocate_memory_for_bfs(data);
	while (augment_paths(data))
		compare_paths(data);
	print_answer(data, input);
	free_all(data, input);
	return (0);
}

