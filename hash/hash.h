/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:07:14 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/23 14:32:31 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include "../libft/includes/libft.h"

typedef struct s_hash
{
	char *name;
	int xy[2];
	int number;
	struct s_hash *links;
	
}			t_hash;

typedef struct s_table
{
	t_hash			*table;
	unsigned long	table_size;
}			t_table;

// INIT
void 			hash_init(unsigned int table_size);
void			hash_destroy(void);

// FUNCTIONS
int				hash_get_number(char *name);
int				*hash_get_coords(char *name);
void			hash_add(char *name, int x, int y, int number);

// STORAGE MANAGEMENT
unsigned long	hash_djb2(char *key);
t_hash			*hash_new(char *name, int x, int y, int number);
t_hash			*hash_get(char *name);
t_table			*hash_storage(void);
#endif