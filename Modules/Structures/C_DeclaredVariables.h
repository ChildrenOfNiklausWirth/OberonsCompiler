#ifndef OBERONSCOMPILER_C_DECLAREDVARIABLES_H
//__________________________________________________________________________________________________

#define OBERONSCOMPILER_C_DECLAREDVARIABLES_H

int DV_INIT_MAXSIZE = 20;

struct DeclaredVariables {
    struct Token *variables;
    int maxSize;
    int size;
};

void dv_allocatedMemory(struct DeclaredVariables *declaredVariables);

void dv_initialize(struct DeclaredVariables *declaredVariables);

void dv_addVarialbe(struct DeclaredVariables *declaredVariables, struct Token *variable);



#endif //OBERONSCOMPILER_C_DECLAREDVARIABLES_H
