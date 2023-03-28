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
    int *q = (int *)my_malloc(sizeof(int));
    if (q == NULL) {
        printf("Error: my_malloc failed\n");
        return 1;
    }
    *q = 20;
    char *s = (char *)my_malloc(10);
    if (s == NULL) {
        printf("Error: my_malloc failed\n");
        return 1;
    }
    s[0] = 'a';
    my_free(q);
    my_free(s);
    return 0;
}