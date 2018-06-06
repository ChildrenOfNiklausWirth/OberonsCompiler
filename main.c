#include "Modules/B_LexAnalyzer.c"

char adress[] = "C:\\Users\\danil\\CLionProjects\\OberonsCompiler\\Tests\\ProgrammsOnOberon\\1_Test.txt";
struct TokensFlow tokensFlow;

int main() {
    lexAnalysis(adress, &tokensFlow);


    return 0;
}

