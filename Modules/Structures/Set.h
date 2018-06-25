#ifndef OBERONSCOMPILER_C_SET_H
#define OBERONSCOMPILER_C_SET_H
int const SET_INIT_MAXSIZE;

struct Set {
    int *digit;
    int size;
    int maxSize;
};

struct Set set_newSet();

void set_initialize(struct Set *set);

void set_allocatedMemory(struct Set *set);

void set_addDigit(struct Set *set, int digit);

int set_contains(struct Set set, int digit);

#endif //OBERONSCOMPILER_C_SET_H
