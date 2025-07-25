#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>

static t_zone *find_zone_containing(void *ptr, t_zone *zone_list, t_zone **prev_out) {
    t_zone *prev = NULL;
    while (zone_list) {
        void *zone_start = zone_list->start;
        void *zone_end = (void *)zone_list + zone_list->total_size;

        if (ptr > zone_start && ptr < zone_end) {
            if (prev_out)
                *prev_out = prev;
            return zone_list;
        }

        prev = zone_list;
        zone_list = zone_list->next;
    }
    return NULL;
}

static void remove_zone(t_zone **zone_list, t_zone *zone_to_remove, t_zone *prev) {
    if (!zone_list || !zone_to_remove)
        return;

    if (prev)
        prev->next = zone_to_remove->next;
    else
        *zone_list = zone_to_remove->next;
}

void free(void *ptr) {
    if (!ptr)
        return;

    t_block *block = (t_block *)ptr - 1;
    t_zone *zone = NULL, *prev = NULL;

    zone = find_zone_containing(ptr, g_memory.tiny, &prev);
    if (zone) {
        block->free = 1;
        return;
    }

    zone = find_zone_containing(ptr, g_memory.small, &prev);
    if (zone) {
        block->free = 1;
        return;
    }

    zone = find_zone_containing(ptr, g_memory.large, &prev);
    if (zone) {
        remove_zone(&g_memory.large, zone, prev);
        munmap(zone, zone->total_size);
        return;
    }
}
