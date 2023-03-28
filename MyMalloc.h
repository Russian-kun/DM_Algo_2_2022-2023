#ifndef __MY_MALLOC_
#define __MY_MALLOC_

#include <stdlib.h>

typedef struct block_t {
    size_t size;
    struct block_t* next;
} block_t;

void my_malloc_init(void);

void* my_malloc(size_t size);

void my_free(void* ptr);

#endif