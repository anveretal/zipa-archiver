#ifndef POINTER_ARRAY_H
#define POINTER_ARRAY_H

#include <stddef.h>

typedef struct {
    size_t size;
    size_t capacity;
    void **data;
} pointerArray_t;

pointerArray_t *pointerArrayCreate(size_t capacity);
void pointerArrayDestroy(pointerArray_t *pointerArray, void (*destroyFunction)(void *));

int pointerArrayAdd(pointerArray_t *pointerArray, void *item);
void *pointerArrayGetAt(pointerArray_t *pointerArray, size_t index);

#endif // POINTER_ARRAY_H
