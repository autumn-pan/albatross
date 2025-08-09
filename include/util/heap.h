#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>

typedef struct heapNode_t
{
    void* value;
    struct heapNode_t* left;
    struct heapNode_t* right;
} HeapNode_t;

typedef struct
{
    HeapNode_t root;
    uint8_t size;
} Heap_t;

#endif