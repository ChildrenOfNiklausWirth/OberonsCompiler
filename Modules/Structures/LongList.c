#include "LongList.h"
#include <stdlib.h>

LongList longList_new() {
    LongList longList;
    longList.array = calloc(0, sizeof(long));
    longList.size = 0;
    return longList;
}

void longList_add(LongList *longList, long digit) {
    longList->size++;
    longList->array = realloc(longList->array, sizeof(long) * (size_t) longList->size);
    longList->array[longList->size - 1] = digit;
}

void longList_print(LongList longList) {
    for (int i = 0; i < longList.size; ++i)
        printf("%lu ", longList.array[i]);

}

int longList_equals(LongList longList1, LongList longList2) {
    if (longList1.size != longList2.size)
        return 0;

    for (int i = 0; i < longList1.size; ++i)
        if (longList1.array[i] != longList2.array[i])
            return 0;

    return 1;
}