#include "Modules/B_LexAnalyzer.h"

char adress[] = "C:\\Users\\danil\\CLionProjects\\OberonsCompiler\\Tests\\ProgrammsOnOberon\\1_Test.txt";
struct TokensFlow tokensFlow;
struct DeclaredVariables declaredVariables;

int main() {
    lexAnalysis(adress, &tokensFlow, &declaredVariables);

    return 0;
}

