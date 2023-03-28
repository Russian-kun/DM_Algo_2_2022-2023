#include "MyMalloc.h"
#include <stdio.h>

int main() {
    my_malloc_init();
    int *p = (int *)my_malloc(sizeof(int));
    if (p == NULL) {
        printf("Error: my_malloc failed\n");
        return 1;
    }
    *p = 10;
    my_free(p);
    return 0;
}