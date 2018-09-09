#include "Set.h"
#include <stdlib.h>

struct Set *set_new() {
    struct Set *set;
    set = calloc(1, sizeof(*set));
    set->maxSize = 1;
    set->size = 0;
    set->array = malloc(sizeof(int) * 1);
    return set;
}

//void set_initialize(struct Set *set) {
//    set->maxSize = 1;
//    set->size = 0;
//    set->array = malloc(sizeof(int) * 1);
//}

void set_allocatedMemory(struct Set *set, int addedMemoryCells) {
    set->maxSize += addedMemoryCells;
    set->array = realloc(set->array, sizeof(int) * set->maxSize);
}

void set_addDigit(struct Set *set, int digit) {
    if (set->size == set->maxSize - 1)
        set_allocatedMemory(set, 1);
    set->array[set->size] = digit;
    set->size++;

}

void set_INCL(struct Set *set, int digit) {
    if (!set_contains(*set, digit))
        set_addDigit(set, digit);
}

void set_delete(struct Set *set, int digit) {
    for (int i = 0; i < set->size; ++i) {
        if (set->array[i] == digit)
            while (i < set->size - 1) {
                set->array[i] = set->array[i + 1];
                i++;
            }
    }
    set->size -= 1;
    set_allocatedMemory(set, -1);

}

void set_EXCL(struct Set *set, int digit) {
    if (set_contains(*set, digit))
        set_delete(set, digit);
}

int set_contains(struct Set set, int digit) {
    for (int i = 0; i < set.size; ++i)
        if (set.array[i] == digit)
            return 1;
    return 0;


}
