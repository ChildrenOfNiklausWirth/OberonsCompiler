#ifndef OBERONSCOMPILER_C_OBJECT_H
#define OBERONSCOMPILER_C_OBJECT_H

struct Type;
struct Object;


struct Type {
    int form;
    struct Object fields;
    struct Type base;
    int size;
    int len;

};

struct Object {
    int class;
    int level;
    struct Object next;
    struct Object dsc;
    struct Type type;
    char *name;
    long val;


};

#endif //OBERONSCOMPILER_C_OBJECT_H
