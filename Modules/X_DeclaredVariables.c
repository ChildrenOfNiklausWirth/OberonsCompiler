//__________________________________________________________________________________________________

struct Variable {
    char name[20];
    int lengthOfName;
    char type;

};

struct Variable v_newVariable(const char name[], int lengthOfName, char type) {
    struct Variable variable;
    variable.lengthOfName = lengthOfName;
    for (int i = 0; i < lengthOfName; ++i)
        variable.name[i] = name[i];
    variable.type = type;
    return variable;
}

//__________________________________________________________________________________________________

struct DeclaredVariables {
    struct Variable variables[50];
    int maxSize;
    int size;

};

dv_initialize(struct DeclaredVariables *declaredVariables) {
    declaredVariables->size = 0;
    declaredVariables->maxSize = 50;
}


dv_addNewVarialbe(struct DeclaredVariables *declaredVariables, struct Variable *variable) {
    declaredVariables->variables[declaredVariables->size] = *variable;
    declaredVariables->size++;
}

//__________________________________________________________________________________________________
