#include "malloc.h"

t_memory g_memory = {NULL, NULL, NULL};

t_zone *create_zone(t_zone_type type, size_t zone_size) 
{
    t_zone *zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone == MAP_FAILED)
        return NULL;

    memset(zone, 0, sizeof(t_zone));

    zone->type = type;
    zone->total_size = zone_size;
    zone->next = NULL;
    zone->start = (void *)zone + sizeof(t_zone);

    t_block *first_block = (t_block *)zone->start;
    first_block->size = zone_size - sizeof(t_zone) - sizeof(t_block);
    first_block->free = 1;
    first_block->next = NULL;
    zone->blocks = first_block;

    return zone;
}

t_zone **get_zone_list(size_t size)
{
    if (size <= TINY_LIMIT)
        return &g_memory.tiny;
    if (size <= SMALL_LIMIT)
        return &g_memory.small;
    return &g_memory.large;
}

size_t get_zone_size(size_t size)
{
    if (size <= TINY_LIMIT)
        return TINY_ZONE_SIZE;
    if (size <= SMALL_LIMIT)
        return SMALL_ZONE_SIZE;
    return size + sizeof(t_zone) + sizeof(t_block);
}

t_block *find_free_block(t_zone *zone, size_t size)
{
    while (zone) {
        t_block *block = zone->blocks;
        while (block) {
            if (block->free && block->size >= size)
                return block;
            block = block->next;
        }
        zone = zone->next;
    }
    return NULL;
}

void append_zone(t_zone **zone_list, t_zone *new_zone)
{
    if (!*zone_list)
        *zone_list = new_zone;
    else {
        t_zone *tmp = *zone_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_zone;
    }
}