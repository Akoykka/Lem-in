/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/08/27 11:39:39 by akoykka          ###   ########.fr       */
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
	char	**name_list;
	int		**adj_grid;
	int		*status;
	int		**paths;
	int		*queue;
	int		q_size;
	int		room_count;
}


#endif