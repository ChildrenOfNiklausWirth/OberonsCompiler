#include <stdlib.h>
#include "C_DeclaredVariables.h"
#include "A_Tokens.h"

//__________________________________________________________________________________________________

void dv_allocatedMemory(struct DeclaredVariables *declaredVariables) {
    declaredVariables->maxSize = declaredVariables->maxSize * 2;
    declaredVariables->variables = realloc(declaredVariables->variables,
                                           sizeof(struct Token) * declaredVariables->maxSize);
}

void dv_initialize(struct DeclaredVariables *declaredVariables) {
    declaredVariables->size = 0;
    declaredVariables->maxSize = DV_INIT_MAXSIZE;
    declaredVariables->variables = malloc(sizeof(struct Token) * DV_INIT_MAXSIZE);
}

void dv_addVarialbe(struct DeclaredVariables *declaredVariables, struct Token *variable) {
    if (declaredVariables->maxSize == 0)
        dv_initialize(declaredVariables);
    if (declaredVariables->size == declaredVariables->maxSize - 1)
        dv_allocatedMemory(declaredVariables);
    declaredVariables->variables[declaredVariables->size] = *variable;
    declaredVariables->size++;
}


