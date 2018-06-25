#include <stdlib.h>
#include "Set.h"


int const SET_INIT_MAXSIZE = 16;

struct Set set_newSet() {
    struct Set set;
    set.maxSize = SET_INIT_MAXSIZE;
    set.size = 0;
    set.digit = malloc(sizeof(int) * SET_INIT_MAXSIZE);
}

void set_initialize(struct Set *set) {
    set->maxSize = SET_INIT_MAXSIZE;
    set->size = 0;
    set->digit = malloc(sizeof(int) * SET_INIT_MAXSIZE);
}

void set_allocatedMemory(struct Set *set) {
    set->maxSize = set->maxSize * 2;
    set->digit = realloc(set->digit, sizeof(int) * set->maxSize);
}

void set_addDigit(struct Set *set, int digit) {
    if (set->size == set->maxSize - 1)
        set_allocatedMemory(set);
    set->digit[set->size] = digit;
    set->size++;

}

int set_contains(struct Set set, int digit) {
    for (int i = 0; i < set.size; ++i)
        if (set.digit[i] == digit)
            return 1;
    return 0;


}
