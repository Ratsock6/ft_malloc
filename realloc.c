/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:24 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/07 13:27:26 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>
#include <unistd.h>

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_block	*block;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	block = (t_block *)ptr - 1;
	if (block->size >= size)
		return (ptr);
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	memcpy(new_ptr, ptr, block->size);
	free(ptr);
	return (new_ptr);
}
