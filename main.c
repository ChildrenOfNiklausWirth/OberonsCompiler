#include "C:\Users\Danila Eremenko\CLionProjects\OberonsCompiler\Modules\A_Parser.c"

char adress[] = "C:\\Users\\Danila Eremenko\\CLionProjects\\OberonsCompiler\\Tests\\ProgrammsOnOberon\\1_Test.txt";
struct TokensFlow tokensFlow;

int main() {
    tokensFlowInitialize(&tokensFlow);
    tokensParsing(adress, &tokensFlow);
    printTokensFlow(tokensFlow);

    return 0;
}

