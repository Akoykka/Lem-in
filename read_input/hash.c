/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:03:31 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/09 19:18:32 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_input.h"

/*
	every cycle of hash function
	Bitshift is faster on cpu ((hash << 5) + hash)
*/
int	is_only_numbers(char *str)
{
	if ((*str == '-' && ft_strlen(str) > 1)
	|| (*str == '+' && ft_strlen(str) > 1))
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

int	is_smaller_than_max(char *str)
{
	if (*str == '+')
		++str;
	if (ft_strlen(str) > 10 
		|| (ft_strlen(str) == 10 && ft_strcmp(str, "2147483647") > 0))
			return (0);
	return (1);
}

int	is_bigger_than_min(char *str)
{
	if (*str == '-')
	{
		if (ft_strlen(str) > 11 
			|| (ft_strlen(str) == 11 && ft_strcmp(str, "-2147483648") > 0))
				return (0);
	}
	return (1);
}

int ft_is_int(char *str)
{
	if (str && is_only_numbers(str)
		&& is_smaller_than_max(str)
 		&& is_bigger_than_min(str))
		return (1);
	return (0);
}



unsigned long hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	while (*str)
	{
		c = *str;
		hash = hash * 33 + c;
		++*str;
	}
	return (hash);
}

int hash_add(t_table *t, unsigned long digest, char **room_data, int room_number)
{
	t_hash *new;

	while ((t->table)[digest])
	{
		++digest;
		if (digest == t->table_size)
			digest = 0;
	}
	new = (t_hash *)ft_memalloc(sizeof(t_hash));
	if (!new)
		return (0);
	new->name = ft_strdup(room_data[0]);
	if (!new->name)
		return (0);
	new->number = room_number;
	(new->xy)[0] = ft_atoi(room_data[1]);
	(new->xy)[1] = ft_atoi(room_data[2]);
	(t->table)[digest] = *new;
	return (1);
}

void save_room(t_path *data, t_table *t, char **room_data)
{
	unsigned long digest;
	char *name;
	t_list *new;

	name = room_data[0];
	digest = hash(name) % t->table_size;
	if (!hash_add(t, digest, room_data, data->room_count))
		exit(1);
	new = ft_lstnew(name, sizeof(char) * ft_strlen(name));
	if (!new)
		exit(1);
	ft_lstadd(&data->room_list, new);
}

int get_room_number(t_table *t, char *room_name)
{
	unsigned long	digest;
	t_hash			*temp;

	temp = t->table;
	digest = hash(room_name) % t->table_size;
	
	while (table[digest] && ft_strcmp((table[digest]).name, room_name))
	{
		++digest;
		if (digest == t->table_size)
			digest = 0;
	}
	if (!table[digest])
	{
			printf("ERROR NO SUCH ROOM get_room_number\n");
			exit(1);
	}
	return ((t->table)[digest].number);
}

void save_link(t_path *data, t_table *t, char *room_name, char *room2_name)
{
	int node1;
	int node2;
	node1 = get_room_number(t, room_name);
	node2 = get_room_number(t, room2_name);
	(data->adj_grid)[node1][node2] = 1;
	(data->adj_grid)[node2][node1] = 1;
}
