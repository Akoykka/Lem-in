/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:19:27 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 18:32:45 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void make_grid(t_path *data)
{
	int i;
	
	i = 0;
	data->best_path = ft_memalloc(sizeof(int) * data->room_count);
	data->adj_grid = (int **)ft_memalloc(sizeof(int *) * data->room_count);
	data->best_turn_count = 2147483647;
	if (!data->adj_grid || !data->best_path)
		exit(1);
	while(data->room_count > i)
	{
		(data->adj_grid)[i] = (int *)ft_memalloc(sizeof(int) * data->room_count);
		if (!(data->adj_grid)[i])
			exit(1);
		++i;
	}
}

int read_stdin(char *buf)
{
	int ret;

	ret = 0;
	ft_memset(buf, 0 , sizeof(char) * 1000 + 1);
	ret = read(0, buf, 1000);
	if (ret == -1)
	{
			ft_putstr("Read Error\n");
			exit(1);
	}
	return (ret);
}

char *memory_realloc(char *src, char *src2)
{
	unsigned int len;
	char *new;

	new = NULL;
	len = 0;

	if (src)
		len += ft_strlen(src);
	if (src2)
		len += ft_strlen(src2);

	new = (char *)ft_memalloc(sizeof(char) * len + 1);
	if(!new)
		exit(1);

	if (src)
		ft_strcat(new, src);
	if (src2)
		ft_strcat(new, src2);

	return(new);
}

char *get_stdin_input(void)
{
	char	*line;
	char	buf[1000 + 1];
	int		ret;
	char	*free_er;

	ret = 0;
	line = NULL;
	ret = read_stdin(buf);
	while (ret)
	{	
		free_er = line;
		line = memory_realloc(line, buf);
		ft_strdel(&free_er);
		ret = read_stdin(buf);
	}

	return(line);
}

void ft_print_array(char **strings)
{
	unsigned int i;

	i = 0;
	if (!strings)
		exit(1);
	while(strings[i])
	{
		ft_putstr(strings[i]);
		ft_putchar('\n');
		++i;
	}
}



char **allocate_memory(t_path *data)
{
	char **lines;

	lines = NULL;
	
	lines = ft_strsplit(get_stdin_input(), '\n');
	//ft_print_array(lines);
	hash_init(ft_array_len(lines) * 3);

	data->room_list = (char **)ft_memalloc(sizeof(char *) * ft_array_len(lines));
	if (!data->room_list)
		exit(1);
	data->room_list[0] = ft_memalloc(sizeof(char) * ft_array_len(lines));
	data->room_count = 1;

	return(lines);
}