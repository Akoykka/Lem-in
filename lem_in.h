/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/29 01:02:32 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define ADJACENT -1
# define NOT_ADJACENT -2
# define START 0
# define SINK 1
# define CLOSED -10
# define OPEN -20
# define LOCKED -30
# define ADJ_GRID (data->adj_grid)
# define ROOM_COUNT (data->room_count)



typedef struct s_path
{
	int		ant_count;
	char	**name_list;
	int		**adj_grid;
	int		**paths;
	int		room_count;
}				t_path;

typedef struct s_queue
{
	int		*queue;
	int		q_size;
}			t_queue;

#endif