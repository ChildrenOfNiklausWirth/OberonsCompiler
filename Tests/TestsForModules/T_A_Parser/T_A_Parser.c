#include "../../../Modules/A_Parser.c"

char adress[] = "C:\\Users\\Danila Eremenko\\CLionProjects\\OberonsCompiler\\Tests\\TestsForModules\\T_A_Parser\\1_Test.txt";
struct TokensFlow tokensFlow;

int main() {
    tf_initialize(&tokensFlow);
    tokensParsing(adress, &tokensFlow);
    printTokensFlow(tokensFlow);
}