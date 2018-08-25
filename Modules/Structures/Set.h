#ifndef OBERONSCOMPILER_C_SET_H
#define OBERONSCOMPILER_C_SET_H
struct Set {
    int *array;
    int size;
    int maxSize;
};

struct Set *set_new();

void set_initialize(struct Set *set);

void set_INCL(struct Set *set, int digit);

void set_EXCL(struct Set *set,int digit);

int set_contains(struct Set set, int digit);

#endif //OBERONSCOMPILER_C_SET_H
