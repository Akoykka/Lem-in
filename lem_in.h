/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:48:43 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/01 22:21:16 by akoykka          ###   ########.fr       */
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
	int		turn_count;
	int		*visited;

}				t_path;

typedef struct s_queue
{
	int		*queue;
	int		size;
}			t_queue;


#endif