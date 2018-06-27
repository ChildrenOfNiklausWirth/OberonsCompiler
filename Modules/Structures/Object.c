#include "Object.h"

int item_equals(struct Item item1, struct Item item2) {
    if (item1.level != item2.level)
        return 0;
    if (item1.mode != item2.mode)
        return 0;
    if (item1.a != item2.a)
        return 0;
    if (item1.b != item2.b)
        return 0;
    if (item1.c != item2.c)
        return 0;
    if (item1.r != item2.r)
        return 0;
    if (type_equals(item1.type, item2.type) == 0)
        return 0;


    return 1;


}




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

int object_equals(struct Object object1, struct Object object2) {
    if (object1.size != object2.size)
        return 0;
    if (object1.level != object2.level)
        return 0;
    if (object1.class != object2.class)
        return 0;
    if (object1.val != object2.val)
        return 0;
    if (object_equals(object1.dsc, object2.dsc) == 0)
        return 0;
    if (object_equals(object1.next, object2.next) == 0)
        return 0;
    if (type_equals(object1.type, object2.type) == 0)
        return 0;
    for (int i = 0; i < object1.size; ++i)
        if (object1.name[i] != object2.name[i])
            return 0;
    return 1;
}



int type_equals(struct Type type1, struct Type type2) {
    if (type1.form != type2.form)
        return 0;
    if (type1.len != type2.len)
        return 0;
    if (type1.size != type2.size)
        return 0;
    if (type_equals(type1.base, type2.base) == 0)
        return 0;
    if (object_equals(type1.fields, type2.fields) == 0)
        return 0;
    return 1;


}