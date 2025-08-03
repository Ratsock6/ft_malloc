#include "malloc.h"

size_t align8(size_t size)
{
    return ((size + 7) & ~7);
}