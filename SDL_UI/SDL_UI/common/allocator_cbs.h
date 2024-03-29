#pragma once

#include <stddef.h>

struct allocator_cbs {
void* (*malloc) (size_t size); 
void* (*realloc) (void* ptr, size_t size); 
void (*free) (void* ptr); 
};
