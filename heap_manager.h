// Eymard Alarcon // 

#ifndef HEAP_MANAGER_H
#define HEAP_MANAGER_H

#include <stddef.h>

void heap_init(size_t size);

void* my_malloc(size_t size);

void my_free(void* ptr);

void* my_realloc(void* ptr, size_t size);

void heap_dump();

#endif // HEAP_MANAGER_H
