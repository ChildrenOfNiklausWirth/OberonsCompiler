#include "Modules/B_LeksAnalyzer.c"

char adress[] = "C:\\Users\\danil\\CLionProjects\\OberonsCompiler\\Tests\\TestsForModules\\T_B_LeksAnalyzer.c\\1_Test.txt";
struct TokensFlow tokensFlow;
struct DeclaredVariables declaredVariables;

int main() {
    tf_initialize(&tokensFlow);
    dv_initialize(&declaredVariables);
    tokensParsing(adress, &tokensFlow, &declaredVariables);
    tf_print(tokensFlow);

    return 0;
}

