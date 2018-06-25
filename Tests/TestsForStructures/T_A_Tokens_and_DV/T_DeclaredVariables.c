#include "../../../Modules/Structures/A_Tokens_And_DV.h"
#include <stdio.h>

int test_dv_initialize() {
    struct DeclaredVariables declaredVariables;
    dv_initialize(&declaredVariables);
    if (declaredVariables.size == 0 && declaredVariables.maxSize == DV_INIT_MAXSIZE)
        return 1;
    return 0;
}

int test_dv_allocatedMemory() {
    struct DeclaredVariables declaredVariables;
    dv_initialize(&declaredVariables);
    dv_allocatedMemory(&declaredVariables);
    if (declaredVariables.size == 0 && declaredVariables.maxSize == DV_INIT_MAXSIZE * 2)
        return 1;
    return 0;
}

int test_dv_addVariable() {
    struct Token token;
    token = token_newTokenWithType("MOD", 3, 10);
    struct TerminalSymbols terminalSymbols;
    tss_initialize(&terminalSymbols);
    struct DeclaredVariables declaredVariables;
    dv_initialize(&declaredVariables);
    for (int i = 0; i < DV_INIT_MAXSIZE * 2; ++i)
        dv_addVarialbe(&declaredVariables, &token, terminalSymbols);
    //TODO
    //if (declaredVariables.maxSize == DV_INIT_MAXSIZE * 4 && declaredVariables.size == DV_INIT_MAXSIZE * 2 &&
    //token_equals(declaredVariables.variables[0], token))
    return 1;

}


int main() {
    int rightTestDigit = 0;
    int maxTestDigit = 3;

    printf("DeclaredVariables Testing...\n\n");

    printf("dv_initialize()...\n");
    if (test_dv_initialize() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("dv_allocatedMemory...\n");
    if (test_dv_allocatedMemory() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("dv_addVariable...\n");
    if (test_dv_addVariable() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");

    return 0;


}