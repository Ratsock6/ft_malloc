#include "malloc.h"
#include <string.h>
#include <unistd.h>

void *realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);

    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    t_block *block = (t_block *)ptr - 1;
    if (block->size >= size)
        return ptr;

    void *new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;

    memcpy(new_ptr, ptr, block->size);

    free(ptr);
    return new_ptr;
}
