#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    printf("===== TEST malloc =====\n");
    char *str = malloc(20);
    if (!str)
        return (printf("malloc failed\n"), 1);
    strcpy(str, "Hello malloc!");
    printf("Allocated and wrote: %s\n", str);

    printf("===== TEST realloc =====\n");
    str = realloc(str, 40);
    if (!str)
        return (printf("realloc failed\n"), 1);
    strcat(str, " Realloc OK.");
    printf("Reallocated and wrote: %s\n", str);

    printf("===== TEST free =====\n");
    free(str);
    printf("Memory freed\n");

    return 0;
}
