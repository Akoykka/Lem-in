/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   march_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:10:37 by okoponen          #+#    #+#             */
/*   Updated: 2022/10/26 16:06:50 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	move_all_ants(t_path *data, char **input)
{
	int	i;

	i = 1;
	print_array(input);
	while (i <= data->ant_count)
	{
		write(1, "L", 1);
		ft_putnbr(i);
		write(1, "-", 1);
		ft_putstr(data->end->name);
		if (i < data->ant_count)
			write(1, " ", 1);
		++i;
	}
	write(1, "\n", 1);
	exit(0);
}

int	start_is_next_to_end(t_path *data)
{
	int	i;

	i = 0;
	while (i < data->end->link_size)
	{
		if (data->end->links[i]->id == data->start->id)
			return (1);
		++i;
	}
	return (0);
}
