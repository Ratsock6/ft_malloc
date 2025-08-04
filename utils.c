/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:29 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/04 14:15:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align8(size_t size)
{
	return ((size + 7) & ~7);
}

t_zone_type	get_zone_type(size_t size)
{
	if (size <= TINY_LIMIT)
		return (TINY);
	else if (size <= SMALL_LIMIT)
		return (SMALL);
	else
		return (LARGE);
}
