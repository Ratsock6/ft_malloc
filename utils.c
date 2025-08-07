/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:29 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/07 13:42:32 by aallou-v         ###   ########.fr       */
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

// Fonction de test
void	print_malloc_call(size_t size, int diff)
{
	char	buf[64];
	int		len;

	len = 0;
	if (diff)
		len = snprintf(buf, sizeof(buf), "malloc called with size: %zu (diff: %d)\n", size, diff);
	else
		len = snprintf(buf, sizeof(buf), "malloc called with size: %zu\n", size);
	write(1, buf, len);
}
