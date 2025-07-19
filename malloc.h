#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>

typedef enum e_zone_type {
    TINY,
    SMALL,
    LARGE
}   t_zone_type;

typedef struct s_block {
    size_t          size;
    int             free;
    struct s_block  *next;
}   t_block;

typedef struct s_zone {
    t_zone_type     type;
    size_t          total_size;
    struct s_zone   *next;
    t_block         *blocks;
    void            *start;
}   t_zone;

typedef struct s_memory {
    t_zone  *tiny;
    t_zone  *small;
    t_zone  *large;
}   t_memory;

extern t_memory g_memory;

#endif
