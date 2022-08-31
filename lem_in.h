/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/31 21:04:47 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define ADJACENT 1
# define START 1
# define END 2
# define ADJ_GRID (data->adj_grid)
# define ROOM_COUNT (data->room_count)

typedef struct s_path
{
	int		ant_count;
	int		room_count;
	char	**name_list;
	int		**adj_grid;
	int		*paths;
	int		*visited;
}				t_path;

typedef struct s_queue
{
	int		*queue;
	int		q_size;
}			t_queue;


#endif