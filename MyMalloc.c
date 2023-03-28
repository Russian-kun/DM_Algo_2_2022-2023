#include "MyMalloc.h"
#include <stdint.h>

#define POOL_SIZE 1000000000 /* 1 Giga */
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
#define HEADER_SIZE (sizeof(size_t))

static char _mem_pool[POOL_SIZE]; /* static pool of memory */
static block_t* free_list = NULL;
static int available = POOL_SIZE;

static void defragment(void) {
    block_t* block = free_list;
    block_t* prev = NULL;

    while (block != NULL) {
        if (prev != NULL && (uintptr_t)prev + HEADER_SIZE + prev->size == (uintptr_t)block) {
            /* Merge the two blocks */
            prev->size += HEADER_SIZE + block->size;
            prev->next = block->next;
            block = prev;
        }

        prev = block;
        block = block->next;
    }
}

static void* allocate_block(size_t size) {
    void* ptr = NULL;
    block_t* block = free_list;
    block_t** indirect = &free_list;

    if (size > POOL_SIZE || size > available) {
        return NULL;
    }

    while (block != NULL) {
        if (block->size >= size) {
            /* Found a block that is large enough */
            size_t remainder = block->size - size;

            if (remainder >= sizeof(block_t) + ALIGNMENT) {
                /* Split the block and create a new one */
                block_t* new_block = (block_t*)((uintptr_t)block + HEADER_SIZE + size);
                new_block->size = remainder - HEADER_SIZE;
                new_block->next = block->next;
                *indirect = new_block;
                ptr = (void*)((uintptr_t)block + HEADER_SIZE);
                block->size = size;
                available -= size;
                return ptr;
            } else {
                /* Use the entire block */
                *indirect = block->next;
                ptr = (void*)((uintptr_t)block + HEADER_SIZE);
                available -= block->size;
                return ptr;
            }
        }

        indirect = &block->next;
        block = block->next;
    }

    if (ptr == NULL) {
        defragment();
        return allocate_block(size);
    }

    return NULL;
}

void my_malloc_init(void) {
    block_t* block = (block_t*)_mem_pool;
    block->size = POOL_SIZE - HEADER_SIZE;
    block->next = NULL;
    free_list = block;
}

void* my_malloc(size_t size) {
    size_t alloc_size = ALIGN(size + HEADER_SIZE);
    void* ptr = allocate_block(alloc_size);

    if (ptr == NULL) {
        return NULL;
    }

    *(size_t*)((uintptr_t)ptr - HEADER_SIZE) = alloc_size;
    return ptr;
}

void my_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    block_t* block = (block_t*)((uintptr_t)ptr - HEADER_SIZE);
    block->size = *(size_t*)((uintptr_t)ptr - HEADER_SIZE);
    block->next = free_list;
    free_list = block;
    available += block->size;
}
