/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:50:35 by aallou-v          #+#    #+#             */
/*   Updated: 2025/08/07 13:42:49 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <unistd.h>
# include <sys/mman.h>
# include <string.h>
# include <stdio.h>

# define TINY_LIMIT 128
# define SMALL_LIMIT 1024

typedef enum e_zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_zone_type;

typedef struct s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
}	t_block;

typedef struct s_zone
{
	t_zone_type		type;
	size_t			total_size;
	struct s_zone	*next;
	t_block			*blocks;
	void			*start;
}	t_zone;

typedef struct s_memory
{
	t_zone	*tiny;
	t_zone	*small;
	t_zone	*large;
}	t_memory;

typedef struct s_norm
{
	size_t	total;
	t_block	*block;
	void	*start;
	void	*end;
}	t_norm;

extern t_memory	g_memory;

// Memory Zone
t_zone		*create_zone(t_zone_type type, size_t zone_size);
t_zone		**get_zone_list(size_t size);
size_t		get_zone_size(size_t size);
t_block		*find_free_block(t_zone *zone, size_t size);
void		append_zone(t_zone **zone_list, t_zone *new_zone);

// Utils
size_t		align8(size_t size);
void		print_malloc_call(size_t size, int diff);

// Fonction
void		free(void *ptr);
void		*malloc(size_t size);
void		show_alloc_mem(void);
t_zone_type	get_zone_type(size_t size);

#endif
