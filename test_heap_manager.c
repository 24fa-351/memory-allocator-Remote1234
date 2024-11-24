#ifdef CUSTOM_ALLOCATOR
#include "heap_manager.h"
#else
#include <stdlib.h>
#define heap_init(size)
#define my_malloc(size)           malloc(size)
#define my_free(ptr)              free(ptr)
#define my_realloc(ptr, new_size) realloc(ptr, new_size)
#define heap_dump()               
#endif

#include <stdio.h>

void run_tests() {
    printf("Initializing heap...\n");
    heap_init(1024);

    printf("Allocating memory...\n");
    void* ptr1 = my_malloc(256);
    heap_dump();

    printf("Allocating more memory...\n");
    void* ptr2 = my_malloc(512);
    heap_dump();

    printf("Freeing memory...\n");
    my_free(ptr1);
    heap_dump();

    printf("Reallocating memory...\n");
    ptr2 = my_realloc(ptr2, 1024);
    heap_dump();

    printf("Cleaning up...\n");
    my_free(ptr2);
    heap_dump();
}

int main() {
    run_tests();
    return 0;
}
