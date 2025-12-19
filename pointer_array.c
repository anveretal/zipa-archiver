#include <stdlib.h>

#include "pointer_array.h"

pointerArray_t *pointerArrayCreate(size_t capacity) {
    pointerArray_t *pointerArray = malloc(sizeof(*pointerArray));
    if (!pointerArray) return NULL;

    pointerArray->data = calloc(capacity, sizeof(void *));
    if (!pointerArray->data) {
        free(pointerArray);
        return NULL;
    }

    pointerArray->size = 0;
    pointerArray->capacity = capacity;

    return pointerArray;
}

/*
 * Для корректной очистки нужно передать функцию очистки.
 * Это может быть либо свою функция, либо free.
 * Можно передать NULL, в случае если элементами массива являются
 * стековые переменные.
 */
void pointerArrayDestroy(pointerArray_t *pointerArray, void (*destroyFunction)(void *)) {
    if (!pointerArray) return;

    for (size_t i = 0; i < pointerArray->size; i++) {
        void *currentItem = pointerArray->data[i];
        if (currentItem) {
            if (destroyFunction)
                destroyFunction(currentItem);
        }
    }

    free(pointerArray->data);
    free(pointerArray);
}



int pointerArrayAdd(pointerArray_t *pointerArray, void *item) {
    if (!pointerArray) return EXIT_FAILURE;

    if (pointerArray->size >= pointerArray->capacity) {
        size_t newCapacity = pointerArray->capacity ? pointerArray->capacity * 2 : 1;

        pointerArray->data = realloc(pointerArray->data, sizeof(void *) * newCapacity);
        if (!pointerArray->data) return EXIT_FAILURE;

        pointerArray->capacity = newCapacity;
    }

    pointerArray->data[pointerArray->size] = item;
    pointerArray->size++;

    return EXIT_SUCCESS;
}

void *pointerArrayGetAt(pointerArray_t *pointerArray, size_t index) {
    if (!pointerArray || index >= pointerArray->size)
        return NULL;

    return pointerArray->data[index];
}
