


#include "libft/includes/libft.h"
#include "lem_in.h"

void queue_remove_head(t_queue *q)
{
	if (!q->size)
		return ;
	ft_memmove(&(q->queue[1]), q->queue, sizeof(int) * q->size);
	q->size--;
}

void queue_add_room(t_queue *q, int room_number)
{
	q->queue[q->size] = room_number;
	++q->size;
}

void queue_add_adjacent(t_path *data, int *paths, t_queue *q)
{
	int room_number;

	room_number = 0;
	while(data->room_count < room_number)
	{
		if(ADJ_GRID[*(q->queue)][room_number] 
			&& room_number != END && room_number != START)
		{
			if (is_collision(paths[room_number]))
				queue_add_room(q, room_number * -1);
			
			if (!paths[room_number])
			{
				paths[room_number] = *(q->queue);
				queue_add(q, room_number);
			}
			
		}
		room_number++;
	}
}

void queue_remove_collision(int collision, t_queue *q)
{
	int i;

	i = 0;
	while (q->size > i && (q->queue)[i] != collision)
		++i;
	ft_memmove((q->queue)[i], (q->queue)[i + 1], sizeof(int) * (q->size - i));
	--q->size;
}


void queue_empty_start_neighbours(t_path *data, t_queue *q)
{
	int room_number;

	room_number = START;
	while(data->room_count > room_number)
	{
		if (data->adj_grid[START][room_number] 
			&& !(data->best_path)[room_number])
			queue_add(q, room_number);
		++room_number;
	}
}