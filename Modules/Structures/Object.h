#ifndef OBERONSCOMPILER_C_OBJECT_H
#define OBERONSCOMPILER_C_OBJECT_H

#include <malloc.h>
struct Item;
struct Object;
struct Type;


struct Item {
    int mode;
    int level;
    struct Type type;
    long a, b, c, r;
};

int item_equals(struct Item item1, struct Item item2);

struct Object {
    int class;
    int level;
    struct Object next;
    struct Object dsc;
    struct Type type;
    char *name;
    int size;
    long val;


};


struct Object object_new();

void object_setName(struct Object obj, char name[], int name_size);

int object_equals(struct Object object1, struct Object object2);

struct Type {
    int form;
    struct Object fields;
    struct Type base;
    int size;
    int len;

};

int type_equals(struct Type type1, struct Type type2);


#endif //OBERONSCOMPILER_C_OBJECT_H
