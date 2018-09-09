#ifndef OBERONSCOMPILER_C_LONGLIST_H
#define OBERONSCOMPILER_C_LONGLIST_H

#include <stdio.h>

typedef struct LongList LongList;

typedef struct LongList {
    long *array;
    int size;
} LongList;


LongList longList_new();

void longList_add(LongList *longList, long digit);

void longList_print(LongList longList);

int longList_equals(LongList longList1, LongList longList2);

#endif //OBERONSCOMPILER_C_LONGLIST_H
