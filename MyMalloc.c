#include "MyMalloc.h"

#define POOL_SIZE 1000000000 /* 1 Giga */

static char _mem_pool[POOL_SIZE]; /* static pool of memory */

void* my_malloc(size_t size) {
    /* Bon courage !!!! */
}

void my_free(void* pouet) {
    /* Bon courage !!!! */
}