#include "malloc.h"

#define TINY_LIMIT 128
#define SMALL_LIMIT 1024

#define TINY_ZONE_SIZE (getpagesize() * 16)
#define SMALL_ZONE_SIZE (getpagesize() * 128)

// Fonction de test
void print_malloc_call(size_t size) {
    char buf[64];
    int len = 0;

    len = snprintf(buf, sizeof(buf), "malloc called with size: %zu\n", size);
    write(1, buf, len);
}

void *malloc(size_t size) {
    size = align8(size);
    if (size == 0)
        return NULL;

    t_zone **zone_list = get_zone_list(size);
    t_zone *zone = *zone_list;
    t_block *block = find_free_block(zone, size);

    if (!block) {
        size_t zone_size = get_zone_size(size);
        t_zone *new_zone = create_zone((size <= TINY_LIMIT) ? TINY :
                                       (size <= SMALL_LIMIT) ? SMALL : LARGE,
                                       zone_size);
        if (!new_zone)
            return NULL;
        append_zone(zone_list, new_zone);
        block = new_zone->blocks;
    }

    block->free = 0;
    return (void *)(block + 1);
}
