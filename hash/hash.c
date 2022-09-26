/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:11:10 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/21 15:54:56 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

unsigned long hash_djb2(char *str)
{
	unsigned long hash = 5381;
	int c;



	while (*str)
	{
		c = *str;
    	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	 	++str;
	}
	/*int c;
	int i;

	i = 0;
	while (key[i])
	{
		c = key[i];
		hash = hash * 33 + c;
		++i;
	}*/
	return (hash);
}

int hash_get_number(char *name)
{
	t_hash *temp;

	temp = hash_get(name);
	return (temp->number);
}

int *hash_get_coords(char *name)
{
	t_hash *temp;

	temp = hash_get(name);
	return (temp->xy);
}

void hash_init(unsigned int table_size)
{
	t_table *temp;

	temp = hash_storage();
	temp->table_size = table_size;
	temp->table = (t_hash *)ft_memalloc(sizeof(t_hash) * table_size);
	if (!temp->table)
		exit(1);
}

void hash_destroy(void)
{
	t_table *temp;
	unsigned long i;
	t_hash *hashtable;
	i = 0;
	temp = hash_storage();
	hashtable = temp->table;
	while (temp->table_size > i)
	{
		if (hashtable[i].name)
		{
			free(hashtable[i].name);
			hashtable[i].name = NULL;
		}
		++i;
	}
}

t_hash *hash_get(char *name)
{
	t_table *temp;
	unsigned long digest;
	t_hash *hash_table;
	if(!name)
		return NULL;

	temp = hash_storage();
	digest = hash_djb2(name) % temp->table_size;
	hash_table = temp->table;

	while (hash_table[digest].name)
	{
		if (!ft_strcmp(hash_table[digest].name, name))
			return(&hash_table[digest]);
		digest++;
		if (temp->table_size == digest)
			digest = 0;
	}
	//printf("%s\n", hash_table[5141].name);
	//printf("maxsize hashtable %lu\n", temp->table_size);
	//ft_putstr("Error, no such name in hashtable (hash_get) Hashname:");
	//printf("(printf)%s\n (putstr)\n", name);
	//ft_putstr(name);
	//printf("digest is %lu\n", digest);
	//ft_putchar('\n');
	//printf("%lu", hash_djb2(name) % temp->table_size);
	exit(1);
}

void hash_add(char *name, int x, int y, int room_count)
{
	t_table *temp;
	unsigned long digest;
	t_hash *hash_table;
	if(!name)
		return ;
	temp = hash_storage();
	digest = hash_djb2(name) % temp->table_size;
	hash_table = temp->table;
	while (hash_table[digest].name)
	{
		digest++;
		if (temp->table_size == digest)
			digest = 0;
	}
	hash_table[digest].name = ft_strdup(name);
	if(!hash_table[digest].name)
		exit(1);
	hash_table[digest].xy[0] = x;
	hash_table[digest].xy[1] = y;
	hash_table[digest].links = (t_hash **)ft_memalloc((sizeof(t_hash *) * room_count - 1));
	if (!hash_table[digest].links)
		exit (1);
}


t_table *hash_storage(void)
{
	static t_table storage;
	return (&storage);
}
