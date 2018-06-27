//
// Created by danil on 25.06.2018.
//

#include <malloc.h>
#include "Object.h"

struct Object object_new() {
    struct Object obj;
    obj.name = calloc(16, sizeof(char));
    return obj;
}

void object_setName(struct Object obj, char name[], int name_size) {
    for (int i = 0; i < sizeof(&name); ++i) {
        obj.name[i] = name[i];
    }
}