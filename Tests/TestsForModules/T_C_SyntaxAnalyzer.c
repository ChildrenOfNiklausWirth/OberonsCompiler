#include "../../Modules/B_LexAnalyzer.h"
#include "../../Modules/C_SyntaxAnalyzer.c"

char adress[] = "..\\Tests\\ProgrammsOnOberon\\1_Test.txt";
struct TokensFlow tokensFlow;
struct DeclaredVariables declaredVariables;


int main() {
    lexAnalysis(adress, &tokensFlow, &declaredVariables);

}