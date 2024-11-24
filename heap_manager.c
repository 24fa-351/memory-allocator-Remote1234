// Eymard Alarcon // 

#include "heap_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

#define BLOCK_SIZE sizeof(Block)

static void* heap_start = NULL;
static void* heap_end = NULL;
static Block* free_list = NULL;

void heap_init(size_t size) {
    heap_start = sbrk(0);
    if (sbrk(size) == (void*)-1) {
        fprintf(stderr, "Error: sbrk failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    heap_end = (char*)heap_start + size;

    free_list = (Block*)heap_start;
    free_list->size = size - BLOCK_SIZE;
    free_list->next = NULL;
}

static void split_block(Block* block, size_t size) {
    size_t remaining_size = block->size - size - BLOCK_SIZE;
    Block* new_block = (Block*)((char*)block + BLOCK_SIZE + size);
    new_block->size = remaining_size;
    new_block->next = block->next;
    block->size = size;
    block->next = new_block;
}

void* my_malloc(size_t size) {
    if (size == 0) return NULL;

    Block* prev = NULL;
    Block* curr = free_list;

    size = (size + 7) & ~7;

    while (curr) {
        if (curr->size >= size) {
            if (curr->size >= size + BLOCK_SIZE + 8) {
                split_block(curr, size);
            }
            if (prev) {
                prev->next = curr->next;
            } else {
                free_list = curr->next;
            }
            return (char*)curr + BLOCK_SIZE;
        }
        prev = curr;
        curr = curr->next;
    }

    fprintf(stderr, "Error: No suitable block found\n");
    return NULL;
}

void my_free(void* ptr) {
    if (!ptr) return;

    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);

    block->next = free_list;
    free_list = block;
}

void* my_realloc(void* ptr, size_t size) {
    if (!ptr) return my_malloc(size);
    if (size == 0) {
        my_free(ptr);
        return NULL;
    }

    Block* block = (Block*)((char*)ptr - BLOCK_SIZE);
    if (block->size >= size) {
        return ptr;
    }

    void* new_ptr = my_malloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
        my_free(ptr);
    }
    return new_ptr;
}

void heap_dump() {
    printf("Heap dump:\n");
    printf("Heap start: %p, Heap end: %p\n", heap_start, heap_end);
    printf("Free list:\n");
    Block* curr = free_list;
    while (curr) {
        printf("  Block at %p, size: %zu\n", curr, curr->size);
        curr = curr->next;
    }
}
