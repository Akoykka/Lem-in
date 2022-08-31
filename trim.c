int is_only_one_neighbour(t_path *data, room_number)
{
	int	neighbour_count;
	int	i;

	i = 0;
	neighbour_count = 0;
	if (room_number != START || room_number != SINK)
		return 0;
	while (ROOM_COUNT > i)
	{
		if (ADJ_GRID[room_number][i] == ADJACENT)
			neighbour_count++;
		if (neighbour_count > 1)
			return (0);
		++i;
	}
	return(1);
}


void trim_nodes(t_path *data)
{
	int found_trim;
	int room_number;

	room_number = 0;
	found_trim = 1;
	while (found_trim)
	{
		found_trim = 0;
		while(ROOM_COUNT > room_number)
		{
			if (is_only_one_neighbour(data, room_number))
			{
				trim(data, room_number);
				found_trim = 1;
			}
			++room_number;
		}	
	}
}


void trim(t_path *data, int room_number)
{
	int i;
	
	i = 0;
	while (ROOM_COUNT > i)
	{
		if (ADJ_GRID[room_number][i] == ADJACENT)
		{
			ADJ_GRID[room_number][i] == NOT_ADJACENT;
			ADJ_GRID[i][room_number] == NOT_ADJACENT;
			return ;
		}
		++i;
	}
}