#include "malloc.h"
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>

#define TINY_LIMIT 128
#define SMALL_LIMIT 1024

#define TINY_ZONE_SIZE (getpagesize() * 16)
#define SMALL_ZONE_SIZE (getpagesize() * 128)

t_memory g_memory = {NULL, NULL, NULL};

static size_t align8(size_t size) {
    return ((size + 7) & ~7);
}

static t_zone *create_zone(t_zone_type type, size_t zone_size) {
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

static t_zone **get_zone_list(size_t size) {
    if (size <= TINY_LIMIT)
        return &g_memory.tiny;
    if (size <= SMALL_LIMIT)
        return &g_memory.small;
    return &g_memory.large;
}

static size_t get_zone_size(size_t size) {
    if (size <= TINY_LIMIT)
        return TINY_ZONE_SIZE;
    if (size <= SMALL_LIMIT)
        return SMALL_ZONE_SIZE;
    return size + sizeof(t_zone) + sizeof(t_block);
}

static t_block *find_free_block(t_zone *zone, size_t size) {
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

static void append_zone(t_zone **zone_list, t_zone *new_zone) {
    if (!*zone_list)
        *zone_list = new_zone;
    else {
        t_zone *tmp = *zone_list;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_zone;
    }
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
