#include "../../Modules/C_SyntaxAnalyzer.c"
#include "../../Modules/Structures/A_Tokens.h"

char address[] = "../Tests/ProgrammsOnOberon/Trigonometry";

int test_declarations() {
    do {
        tf_next(&lexTokensFlow);
    } while (!namesEquals(lexTokensFlow.current->symbols, lexTokensFlow.current->length,
                          "TYPE", sizeof("TYPE") - 1));


    long varsize = 0;
    declarations(&varsize);


    if (varsize == 56)
        return 1;
    return 0;


}

int test_procedureDeclaration() {

    procedureDeclaration();



}


int main() {
    int rightTestDigit = 0;
    int maxTestDigit = 1;


    lexAnalysis(address);
    scope_initialise();
    Open();
    openScope();


    printf("Syntax Analyzer Testing...\n\n");


    printf("test declarations...\n");
    if (test_declarations() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("test procedureDeclarations...\n");
    if (test_procedureDeclaration() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");


}