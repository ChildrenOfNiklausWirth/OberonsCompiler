#include "../../Modules/C_SyntaxAnalyzer.c"
#include "../../Modules/Structures/A_Tokens.h"

char address[] = "../Tests/ProgrammsOnOberon/Trigonometry";

void test_intitialize() {
    lexAnalysis(address);
    scope_initialise();
    Open();
    openScope();

}

int test_declarations() {
    test_intitialize();
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
    test_intitialize();

    do {
        tf_next(&lexTokensFlow);
    } while (!namesEquals(lexTokensFlow.current->symbols, lexTokensFlow.current->length,
                          "PROCEDURE", sizeof("PROCEDURE") - 1));
    procedureDeclaration();


}


int main() {


    int rightTestDigit = 0;
    int maxTestDigit = 1;

    printf("Syntax Analyzer Testing...\n\n");


    printf("test_declarations...\n");
    if (test_declarations() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");


}