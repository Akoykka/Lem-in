/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   march_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:47:36 by okoponen          #+#    #+#             */
/*   Updated: 2022/10/27 10:09:16 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void realloc_check(t_print *print, int ant_num, int dest)
{
	char *temp;

	temp = NULL;
	if (ft_strlen(print->room_list[ant_num]->name)
		 + ft_strlen(print->room_list[dest]->name)
		+ print->moves_len + 3 >= (size_t)print->moves_size)
	{
		temp = (char *)ft_memalloc(sizeof(char) * (print->moves_size * 2));
		if (!temp)
			error("ERROR: malloc failed (realloc_check)", 2);
		ft_strcpy(temp, print->moves);
		free(print->moves);
		print->moves = temp;
	}
}


void strcat_move(t_print *print, int ant_num, int dest)
{
	if (dest == print->end->id)
		--print->ants_left;
	realloc_check(print, ant_num, dest);
	print->moves[print->moves_len++] = 'L';
	ft_strcat(&print->moves[print->moves_len], print->room_list[ant_num]->name);
	print->moves_len += strlen(print->room_list[ant_num]->name);
	print->moves[print->moves_len++] = '-';
	ft_strcat(&print->moves[print->moves_len], print->room_list[dest]->name);
	print->moves_len += strlen(print->room_list[dest]->name);
	print->moves[print->moves_len++] = ' ';
}

void strcat_new_ant(t_print *print, int dest)
{
	static int ant_num = 0;

	++ant_num;
	strcat_move(print, ant_num ,dest);
}

int is_ants_left(t_print *print, int distance_to_end)
{
	if (distance_to_end > print->path_count / print->ants_left)
	{
		return (1);
	}
	return (0);
}


void strcat_path(t_print *print, int curr_path)
{
	int pathlen = 1;
	if (print->ant[curr_path])
	{
		strcat_move(print, print->ant[curr_path], print->end->id);
		print->ant[curr_path] = 0;
	}
	while (print->paths[curr_path] != print->start->id)
	{
		if (print->ant[print->paths[curr_path]])
			strcat_move(print, print->ant[print->paths[curr_path]], curr_path);
		curr_path = print->paths[curr_path];
		pathlen++;
	}
}

void	strcat_one_line(t_print *print)
{
	int tmp;
	int i;

	tmp = 0;
	i = 0;
	while (print->end->link_size > i)
	{
		tmp = print->end->links[i]->id;
		if (print->paths[tmp])
			strcat_path(print, tmp);
		++i;
	}
}

void prepare_print(t_path *data, t_print *print)
{
	int i;
	int path_count;

	path_count = 0;
	i = 0;
	ft_bzero(print, sizeof(t_print));
	print->room_list = data->room_list;
	print->start = data->start;
	print->end = data->end;
	print->paths = data->winner;
	print->ant = (int *)ft_memalloc(sizeof(int) * data->room_count);
	print->moves = (char *)ft_memalloc(sizeof(char) * 1024);
	if (!print->moves || !print->ant)
		error("ERROR: malloc failed at prepare_print", 2);
	print->moves_size = 1024;
	print->ants_left = data->ant_count;
	while (print->end->link_size > i)
	{
		if(print->paths[print->end->links[i]->id])
			++path_count;
		++i;
	}
	print->path_count = path_count;
}

void	print_answer(t_path *data, char **input)
{
	t_print	print;

	if (data->winner_turns == -1)
		error("ERROR: No answer", 52);
	print_array(input);
	prepare_print(data, &print);
	while (print.ants_left)
	{
		ant_distributor(&print);
		strcat_one_line(&print);
		print.moves[print.moves_len++] = '\n';
	}
	print.moves[print.moves_len] = '\0';
	ft_putstr(print.moves);
	free(print.ant);
	free(print.moves);
}