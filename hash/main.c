/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 16:49:49 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/13 17:24:03 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include <stdio.h>

void hash_debug_print_table(void)
{
	t_table *storage;
	unsigned int total_spaces;

	total_spaces = 0;
	storage = hash_storage();
	unsigned long i = 0;

	while(i < storage->table_size)
	{
		if(!(storage->table)[i])
			printf("------ NULL \n");
		else
		{
			printf("Occupied by %s\n", (storage->table)[i]->name);
			++total_spaces;
		}
		++i;
	}
	printf("total spaces occupied = %i\n", total_spaces);
}



int main(void)
{
	hash_init(300);

	hash_add("name", 3, 4 ,139);
	hash_add("pipulo", 3, 4 ,312);
	hash_add("kolvi", 3, 4 ,109);
	hash_add("nddddd", 3, 4 ,77);
	hash_add("nsasd", 3, 4 ,55);
	hash_add("nDDDD", 3, 4 ,32);
	
	hash_debug_print_table();
	printf("Hash_number = %i\n", hash_get_number("pipulo"));
	printf("Hash_number = %i\n", hash_get_number("kolvi"));
	printf("Hash_number = %i\n", hash_get_number("nsasd"));
	printf("Hash_number = %i\n", hash_get_number("nDDDD"));
	hash_destroy();
}