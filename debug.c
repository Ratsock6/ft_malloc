#include "malloc.h"
#include <unistd.h>
#include <stdio.h>

static void print_address(void *addr) {
    printf("%p", addr);
}

static void print_zone_type(t_zone_type type) {
    if (type == TINY)
        write(1, "TINY : ", 7);
    else if (type == SMALL)
        write(1, "SMALL : ", 8);
    else if (type == LARGE)
        write(1, "LARGE : ", 8);
}

static void show_zone_list(t_zone *zone) {
    size_t total = 0;

    while (zone) {
        print_zone_type(zone->type);
        print_address(zone);
        write(1, "\n", 1);

        t_block *block = zone->blocks;
        while (block) {
            if (!block->free) {
                void *start = (void *)(block + 1);
                void *end = start + block->size;
                print_address(start);
                write(1, " - ", 3);
                print_address(end);
                printf(" : %zu octets\n", block->size);
                total += block->size;
            }
            block = block->next;
        }

        zone = zone->next;
    }

    printf("Total : %zu octets\n\n", total);
}

void show_alloc_mem(void) {
    show_zone_list(g_memory.tiny);
    show_zone_list(g_memory.small);
    show_zone_list(g_memory.large);
}
