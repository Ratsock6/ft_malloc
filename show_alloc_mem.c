/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:26 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/07 13:23:57 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

static void	print_address(void *addr)
{
	printf("%p", addr);
}

static void	print_zone_type(t_zone_type type)
{
	if (type == TINY)
		write(1, "TINY : ", 7);
	else if (type == SMALL)
		write(1, "SMALL : ", 8);
	else if (type == LARGE)
		write(1, "LARGE : ", 8);
}

static void	print_show_zone_list(t_norm *norm)
{
	print_address(norm->start);
	write(1, " - ", 3);
	print_address(norm->end);
	printf(" : %zu bytes\n", norm->block->size);
}

static void	show_zone_list(t_zone *zone)
{
	t_norm	norm;

	norm.total = 0;
	while (zone)
	{
		print_zone_type(zone->type);
		print_address(zone);
		write(1, "\n", 1);
		norm.block = zone->blocks;
		while (norm.block)
		{
			if (!norm.block->free)
			{
				norm.start = (void *)(norm.block + 1);
				norm.end = norm.start + norm.block->size;
				print_show_zone_list(&norm);
				norm.total += norm.block->size;
			}
			norm.block = norm.block->next;
		}
		zone = zone->next;
	}
	printf("Total : %zu octets\n\n", norm.total);
}

void	show_alloc_mem(void)
{
	show_zone_list(g_memory.tiny);
	show_zone_list(g_memory.small);
	show_zone_list(g_memory.large);
}
