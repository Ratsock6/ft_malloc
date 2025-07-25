#include "main.h"

int main()
{
    printf("=== Allocation ===\n");
    void *p1 = malloc(10000);

    printf("%p\n", p1);

    show_alloc_mem();

    printf("-----------------------------\n");

    free(p1);

    show_alloc_mem();
}