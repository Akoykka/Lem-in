/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:03:31 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/07 15:33:48 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


/* 
	every cycle of hash function
	Bitshift is faster on cpu ((hash << 5) + hash)
*/
int hash(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;

	while (*str)
	{
		c = *str;
		hash = hash * 33 + c; 
		++*str;
	}
	return (hash % HASH_SIZE);
}

save_room()
