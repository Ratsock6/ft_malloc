/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_zone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:22 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/07 14:35:36 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_memory	g_memory = {NULL, NULL, NULL};


t_zone	*create_zone(t_zone_type type, size_t zone_size)
{
	t_zone	*zone;
	t_block	*first_block;

	zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone == MAP_FAILED)
		return (NULL);
	memset(zone, 0, sizeof(t_zone));
	zone->type = type;
	zone->total_size = zone_size;
	zone->next = NULL;
	zone->start = (void *)zone + sizeof(t_zone);
	first_block = (t_block *)zone->start;
	first_block->size = zone_size - sizeof(t_zone) - sizeof(t_block);
	first_block->free = 1;
	first_block->next = NULL;
	zone->blocks = first_block;
	return (zone);
}

t_zone	**get_zone_list(size_t size)
{
	if (size <= TINY_LIMIT)
		return (&g_memory.tiny);
	if (size <= SMALL_LIMIT)
		return (&g_memory.small);
	return (&g_memory.large);
}

size_t	get_zone_size(size_t size)
{
	if (size <= TINY_LIMIT)
		return (size + sizeof(t_zone) + sizeof(t_block));
	if (size <= SMALL_LIMIT)
		return (size + sizeof(t_zone) + sizeof(t_block));
	return (size + sizeof(t_zone) + sizeof(t_block));
}

t_block	*find_free_block(t_zone *zone, size_t size)
{
	t_block	*block;

	while (zone)
	{
		block = zone->blocks;
		while (block)
		{
			if (block->free && block->size >= size)
				return (block);
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

void	append_zone(t_zone **zone_list, t_zone *new_zone)
{
	t_zone	*tmp;

	if (!*zone_list)
		*zone_list = new_zone;
	else
	{
		tmp = *zone_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_zone;
	}
}
