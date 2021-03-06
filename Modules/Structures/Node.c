#include "Node.h"
#include <stdio.h>
#include <malloc.h>
#include "../LexAnalyzer.h"

Node* node_new() {
    Node *node = calloc(1, sizeof *node);
    return node;
}

void node_setName(Node *obj, char *name, int name_size) {

    if (obj->name == NULL) {
        obj->name = calloc((size_t) name_size, sizeof(char));
    } else {
        obj->name = realloc(obj->name, name_size * sizeof(char));
    }

    obj->nameLength = name_size;

    for (int i = 0; i < obj->nameLength; ++i) {
        obj->name[i] = name[i];
    }
}

int nodes_equals(Node object1, struct Node object2) {
    if (object1.nameLength != object2.nameLength)
        return 0;
    if (object1.level != object2.level)
        return 0;
    if (object1.class != object2.class)
        return 0;
    if (object1.val != object2.val)
        return 0;
    if (nodes_equals(*object1.dsc, *object2.dsc) == 0)
        return 0;
    if (nodes_equals(*object1.next, *object2.next) == 0)
        return 0;
    if (type_equals(*object1.type, *object2.type) == 0)
        return 0;
    for (int i = 0; i < object1.nameLength; ++i)
        if (object1.name[i] != object2.name[i])
            return 0;
    return 1;
}



int type_equals(Type type1, Type type2) {
    if (type1.form != type2.form)
        return 0;
    if (type1.len != type2.len)
        return 0;
    if (type1.size != type2.size)
        return 0;
    if (type_equals(*type1.base, *type2.base) == 0)
        return 0;
    if (nodes_equals(*type1.fields, *type2.fields) == 0)
        return 0;
    return 1;
}

Type *type_new() {
    Type *type = calloc(sizeof(Type), 1);

    if (type != NULL)
        return type;
    else {
        printf("Error while allocating memory for new type\nLine: %i", lexTokensFlow.current->line);
        return NULL;
    }
}