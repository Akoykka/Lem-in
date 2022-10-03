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
