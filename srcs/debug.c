#include "../includes/lem_in.h"
#include <stdio.h>

void p_p(t_path *data, int *paths)
{
	int i;

	i = 1;
	printf("paths is =");

	while(data->room_count > i)
	{
		printf("|%i|", paths[i]);
		printf("Name: %s \n ", data->room_list[paths[i]]->name);
		++i;
	}
	printf("\n");
}

void print_int_array(int *arr, int size)
{
	int i;

	i = 0;
	printf("paths is =\n");

	while(size > i)
	{
		printf("paths[%d]: |%i|\n", i, arr[i]);
		++i;
	}
	printf("\n");
}

void p_q()
{
	int *queue;
	int size;
	int i;

	i = 0;
	queue = q_get_list();
	size = q_get_len();

	printf("q_print:");
	while(size > i)
	{
		printf("%i - ", queue[i]);
		++i;
	}
	printf("\n");
	free(queue);
	queue = NULL;
}
/*
void printq_room_names(t_path *data)
{
	int *queue;
	int size;
	int i;

	i = 0;
	queue = q_get_list();
	size = q_get_len();
	while(size--)
	{
		if(queue[size] < 0)
			printf("%s - ", data->room_list[-queue[size]]);
		else
			printf("%s - ", data->room_list[queue[size]]);
		++i;
	}
	free(queue);
	queue = NULL;
}

void	print_one_path(t_path *data, int j, int *path)
{
	int last_node = j;
	if (j < 0)
		j *= -1;
	q_add_queue(data->room_count);
	printf("Start - ");
	while (path[j] != data->start)
	{
		q_enqueue(path[j]);
		j = path[j];
		if(j < 0)
			j *= -1;
	}
	printq_room_names(data);
	printf("%s - %s \n", data->room_list[last_node], data->room_list[data->end]);
	q_delete_queue();
}

void print_real_paths(t_path *data, int *path)
{
	int i;

	i = 0;
	q_add_queue(data->room_count);
	while (i < data->room_count)
	{
		if (data->adj_grid[data->end][i] && path[i])
			q_enqueue(i);
		++i;
	}
	while (!q_is_empty())
	{
		print_one_path(data, q_peek(), path);
		q_dequeue();
	}
	q_delete_queue();

}
*/
void hash_debug_print_table(void)
{
	t_table *storage;
	unsigned int total_spaces;

	total_spaces = 0;
	storage = hash_storage();
	unsigned long i = 0;

	while(i < storage->table_size)
	{
		if(!(storage->table)[i].name)
			printf("------ NULL \n");
		else
		{
			printf("Occupied by %s\n", (storage->table)[i].name);
			++total_spaces;
		}
		++i;
	}
	printf("total spaces occupied %i\n out of %lu\n", total_spaces, i);

}
/*
void queue_paths_in_print(t_path *data)
{
	int i;

	i = 0;
	while(data->room_count > i)
	{
		if(data->adj_grid[data->end][i] && data->best_path[i])
		{
			q_enqueue(i);
		}
		++i;
	}
}

void ft_print_matrix(t_path *data)
{
	int i;
	int j;

	i = 0;
	while(data->room_count > i)
	{
		j = 0;
		while(data->room_count > j)
		{
			ft_putnbr(data->adj_grid[i][j++]);
		}
		++i;
	}
}


void print_neigbours(t_path *data, int room)
{
	int i;

	i = 0;
	printf("Room-name: |%s| index |%i| neighbours are: \n", data->room_list[room], room);
	while(data->room_count > i)
	{
		if(data->adj_grid[room][i])
			printf("Room name:|%s| index|%i|\n",data->room_list[i], i);
		++i;
	}
}
*/

void dem_paths(t_path *data, int *path)
{
	int i;
	int j;
	int y;
	int temp[data->room_count];

	y = 0;
	while (data->end->links[y])
	{
		i = data->end->links[y]->id;
		j = 0;
		while (i != data->start->id)
		{
			temp[j] = path[i];
			i = path[i];
		}
		printf("len = %d ", j);
		while (j)
		{
			printf("%s |%d|-", data->room_list[temp[j]]->name, j);
			j--;
		}
		printf("\n");
		y++;
	}
}

void print_rooms(t_path *data)
{
	int i = 1;

	printf("Name:\t");
	while(i < data->room_count)
	{
		printf("%s\t", data->room_list[i++]->name);
	}
	printf("\n");

}

void print_wtabs_list(int *list, int size)
{
	int i = 1;
	while(size--)
	{
		printf("%i\t", list[i++]);
	}
	printf("\n");
}
void print_numbers(t_path *data)
{
	int i = 1;
	printf("\t");
	while(i < data->room_count)
	{
		printf("%i\t", i++);
	}
	printf("\n");
}

void nodes_next_to_end(t_path *data)
{
	int i;

	i = 0;
	printf("\nnodes adj to end: ");
	while(data->end->links[i])
	{
		printf("%s (#%i)  ", data->room_list[data->end->links[i]->id]->name, data->room_list[data->end->links[i]->id]->id);
		++i;
	}
	printf("\n");

}

void print_pathnames(t_path *data, int *arr, int size)
{
	int i;

	i = 0;
	while(size > i)
	{
		printf(" |%s|(#%i) -",data->room_list[arr[i]]->name, arr[i]);
		++i;
	}
}

void path_printer(t_path *data, int *paths)
{
	int counter = 1;
	int i = 0;
	int temp;
	q_add_queue(data->room_count);
	while(data->end->links[i])
	{
		temp = data->end->links[i]->id;
		while (temp && temp != data->start->id)
		{
			q_enqueue(temp);
			temp = paths[temp];
		}
		printf("%i. [LEN=%i]\t", counter++, q_get_len());
		printf("(start)|%s|(#%i) -", data->start->name, data->start->id);
		print_pathnames(data, (ft_invert_int_array(q_get_list(), q_get_len())), q_get_len());
		printf(" (end)|%s|(#%i)\n", data->end->name, data->end->id);
		q_bzero();
		++i;
	}
	q_delete_queue();
}


void print_data(t_path *data)
{
	printf("ant_count is: %i\n", data->ant_count);
	printf("room_count is: %i\n", data->room_count);
	printf("start_id:\t%i\tstart_name:\t%s\n", data->start_id, data->room_list[data->start_id]->name);
	printf("end_id:\t\t%i \tend_name:\t%s\n", data->end_id, data->room_list[data->end_id]->name);
	printf("winner_turn is:\t%i\n\n", data->winner_turns);


	print_numbers(data);
	print_rooms(data);
	printf("\nCUR\t");
	print_wtabs_list(data->current_paths, data->room_count);
	printf("WIN\t");
	print_wtabs_list(data->winner, data->room_count);

	printf("\nRES\t");
	print_wtabs_list(data->residue, data->room_count);

	printf("Winner Paths are:\n");
	path_printer(data, data->winner);
	printf("Current Paths are:\n");
	path_printer(data, data->current_paths);
	printf("Residual Paths are:\n");
	path_printer(data, data->residue);
	//printf("1ST\t");
	//print_wtabs_list(data->first_full_set, data->room_count);

	nodes_next_to_end(data);






}