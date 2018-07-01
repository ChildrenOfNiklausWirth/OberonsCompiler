#ifndef OBERONSCOMPILER_C_OBJECT_H
#define OBERONSCOMPILER_C_OBJECT_H

#include <malloc.h>
struct Item;
typedef struct Node Node;
typedef struct type Type;

typedef struct type {
    int form;
    Node *fields;
    Type *base;
    int size;
    int len;

} Type;

Type *type_new();

int type_equals(Type type1, Type type2);

struct Item {
    int mode;
    int level;
    Type *type;
    long a, b, c, r;
};

int item_equals(struct Item item1, struct Item item2);

typedef struct Node {
    int class;
    int level;
    Node *next;
    Node *dsc;
    Type *type;
    char *name;
    int size;
    long val;
} Node;


Node *node_new();

void object_setName(struct Node *obj, char name[], int name_size);

int object_equals(struct Node object1, struct Node object2);


#endif //OBERONSCOMPILER_C_OBJECT_H
