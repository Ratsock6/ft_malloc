/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:17 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/07 13:33:16 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#define TINY_LIMIT 128
#define SMALL_LIMIT 1024

void	*malloc(size_t size)
{
	t_zone	**zone_list;
	t_zone	*zone;
	t_block	*block;
	size_t	zone_size;
	t_zone	*new_zone;

	size = align8(size);
	if (size == 0)
		return (NULL);
	zone_list = get_zone_list(size);
	zone = *zone_list;
	block = find_free_block(zone, size);
	if (!block)
	{
		zone_size = get_zone_size(size);
		new_zone = create_zone(get_zone_type(size), zone_size);
		if (!new_zone)
			return (NULL);
		append_zone(zone_list, new_zone);
		block = new_zone->blocks;
	}
	block->free = 0;
	return ((void *)(block + 1));
}
