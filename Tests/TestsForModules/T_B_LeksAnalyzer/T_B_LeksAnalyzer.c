#include "../../../Modules/B_LexAnalyzer.h"

char adress[] = "C:\\Users\\danil\\CLionProjects\\OberonsCompiler\\Tests\\TestsForModules\\T_B_LeksAnalyzer\\1_Test.txt";
struct TokensFlow tokensFlow;
struct TokensFlow rightTokensFlow;
struct DeclaredVariables declaredVariables;

void createRightResultForFirstTest(struct TokensFlow *tokensflow) {
    struct Token token[50];
    int tokenSize = 42;

    // /MODULE TEST;
    token[0] = token_newTokenWithType("MODULE", 6, 63);
    token[1] = token_newTokenWithType("TEST", 4, 37);
    token[2] = token_newTokenWithType(";", 1, 38);

    //CONST IntConst = 16;
    token[3] = token_newTokenWithType("CONST", 5, 57);
    token[4] = token_newTokenWithType("IntConst", 8, 37);
    token[5] = token_newTokenWithType("=", 1, 9);
    token[6] = token_newTokenWithType("16", 2, 34);
    token[7] = token_newTokenWithType(";", 1, 38);

    //VAR sum: INTEGER;
    token[8] = token_newTokenWithType("VAR", 3, 59);
    token[9] = token_newTokenWithType("sum", 3, 37);
    token[10] = token_newTokenWithType(":", 1, 20);
    token[11] = token_newTokenWithType("INTEGER", 7, 58);
    token[12] = token_newTokenWithType(";", 1, 38);

    //BoolVar: BOOLEAN;
    token[13] = token_newTokenWithType("BoolVar", 7, 37);
    token[14] = token_newTokenWithType(":", 1, 20);
    token[15] = token_newTokenWithType("BOOLEAN", 7, 58);
    token[16] = token_newTokenWithType(";", 1, 38);


    //PROCEDURE AddIntegers(a: INTEGER; b: INTEGER);
    token[17] = token_newTokenWithType("PROCEDURE", 9, 60);
    token[18] = token_newTokenWithType("AddIntegers", 11, 37);
    token[19] = token_newTokenWithType("(", 1, 29);
    token[20] = token_newTokenWithType("a", 1, 37);
    token[21] = token_newTokenWithType(":", 1, 20);
    token[22] = token_newTokenWithType("INTEGER", 7, 58);
    token[23] = token_newTokenWithType(";", 1, 38);
    token[24] = token_newTokenWithType("b", 1, 37);
    token[25] = token_newTokenWithType(":", 1, 20);
    token[26] = token_newTokenWithType("INTEGER", 7, 58);
    token[27] = token_newTokenWithType(")", 1, 22);
    token[28] = token_newTokenWithType(";", 1, 38);

    //BEGIN
    token[29] = token_newTokenWithType("BEGIN", 5, 61);

    //sum := a + b;
    token[30] = token_newTokenWithType("sum", 3, 37);
    token[31] = token_newTokenWithType(":=", 2, 33);
    token[32] = token_newTokenWithType("a", 1, 37);
    token[33] = token_newTokenWithType("+", 1, 6);
    token[34] = token_newTokenWithType("b", 1, 37);
    token[35] = token_newTokenWithType(";", 1, 38);

    //END AddIntegers;
    token[36] = token_newTokenWithType("END", 3, 40);
    token[37] = token_newTokenWithType("AddIntegers", 11, 37);
    token[38] = token_newTokenWithType(";", 1, 38);

    //END TEST;
    token[39] = token_newTokenWithType("END", 3, 40);
    token[40] = token_newTokenWithType("TEST", 4, 37);
    token[41] = token_newTokenWithType(";", 1, 38);


    //TODO problems on 31 step
    for (int i = 0; i < tokenSize; ++i)
        tf_addToken(tokensflow, &token[i]);


}

void assertEquals(struct TokensFlow tokensFlow, struct TokensFlow rightTokensFlow) {
    int result = tf_equals(tokensFlow, rightTokensFlow);
    if (result == 1)
        printf("True");
    else if (result == 0) {
        printf("False\n");
        if (tokensFlow.size != rightTokensFlow.size)
            printf("Not equal size of TokensFlow");
        for (int i = 0; i < rightTokensFlow.size; ++i) {
            if (tokensFlow.tokens[i].size != rightTokensFlow.tokens[i].size ||
                tokensFlow.tokens[i].type != rightTokensFlow.tokens[i].type)
                printf("Not equal type (number %d)", i);
            for (int j = 0; j < tokensFlow.tokens[i].size; ++j) {
                if (tokensFlow.tokens[i].symbols[j] != rightTokensFlow.tokens[i].symbols[j])
                    printf("Not equal name(number %d letter %d", i, j);
            }
        }

    }
}

int main() {
    tf_initialize(&rightTokensFlow);

    createRightResultForFirstTest(&rightTokensFlow);
    tokensParsing(adress, &tokensFlow, &declaredVariables);
    tf_printWithType(tokensFlow);

    printf("\n2 Test Result:\n");
    assertEquals(tokensFlow, rightTokensFlow);

}

