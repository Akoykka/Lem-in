/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoykka <akoykka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:50:03 by akoykka           #+#    #+#             */
/*   Updated: 2022/09/08 13:19:04 by akoykka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	is_only_numbers(char *str)
{
	if ((*str == '-' && ft_strlen(str) > 1)
	|| (*str == '+' && ft_strlen(str) > 1))
		++str;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

static int	is_smaller_than_max(char *str)
{
	if (*str == '+')
		++str;
	if (ft_strlen(str) > 10
		|| (ft_strlen(str) == 10 && ft_strcmp(str, "2147483647") > 0))
			return (0);
	return (1);
}

static int	is_bigger_than_min(char *str)
{
	if (*str == '-')
	{
		if (ft_strlen(str) > 11
			|| (ft_strlen(str) == 11 && ft_strcmp(str, "-2147483648") > 0))
				return (0);
	}
	return (1);
}

int ft_is_int(char *str)
{
	if (str && is_only_numbers(str)
		&& is_smaller_than_max(str)
 		&& is_bigger_than_min(str))
		return (1);
	return (0);
}