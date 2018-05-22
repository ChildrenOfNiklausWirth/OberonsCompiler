#include "../../../Modules/B_LeksAnalyzer.c"

char adress[] = "C:\\Users\\danil\\CLionProjects\\OberonsCompiler\\Tests\\TestsForModules\\T_B_LeksAnalyzer.c\\1_Test.txt";
struct TokensFlow tokensFlow;
struct TokensFlow rightTokensFlow;
struct DeclaredVariables declaredVariables;

void createRightResultForFirstTest(struct TokensFlow *tokensflow) {
    struct Token token[50];
    int tokenSize = 42;

    // /MODULE TEST;
    token[0] = newTokenWithType("MODULE", 6, 63);
    token[1] = newTokenWithType("TEST", 4, 37);
    token[2] = newTokenWithType(";", 1, 38);

    //CONST IntConst = 16;
    token[3] = newTokenWithType("CONST", 5, 57);
    token[4] = newTokenWithType("IntConst", 8, 37);
    token[5] = newTokenWithType("=", 1, 9);
    token[6] = newTokenWithType("16", 2, 34);
    token[7] = newTokenWithType(";", 1, 38);

    //VAR sum: INTEGER;
    token[8] = newTokenWithType("VAR", 3, 59);
    token[9] = newTokenWithType("sum", 3, 37);
    token[10] = newTokenWithType(":", 1, 20);
    token[11] = newTokenWithType("INTEGER", 7, 58);
    token[12] = newTokenWithType(";", 1, 38);

    //BoolVar: BOOLEAN;
    token[13] = newTokenWithType("BoolVar", 7, 37);
    token[14] = newTokenWithType(":", 1, 20);
    token[15] = newTokenWithType("BOOLEAN", 7, 58);
    token[16] = newTokenWithType(";", 1, 38);


    //PROCEDURE AddIntegers(a: INTEGER; b: INTEGER);
    token[17] = newTokenWithType("PROCEDURE", 9, 60);
    token[18] = newTokenWithType("AddIntegers", 11, 37);
    token[19] = newTokenWithType("(", 1, 29);
    token[20] = newTokenWithType("a", 1, 37);
    token[21] = newTokenWithType(":", 1, 20);
    token[22] = newTokenWithType("INTEGER", 7, 58);
    token[23] = newTokenWithType(";", 1, 38);
    token[24] = newTokenWithType("b", 1, 37);
    token[25] = newTokenWithType(":", 1, 20);
    token[26] = newTokenWithType("INTEGER", 7, 58);
    token[27] = newTokenWithType(")", 1, 22);
    token[28] = newTokenWithType(";", 1, 38);

    //BEGIN
    token[29] = newTokenWithType("BEGIN", 5, 61);

    //sum := a + b;
    token[30] = newTokenWithType("sum", 3, 37);
    token[31] = newTokenWithType(":=", 2, 33);
    token[32] = newTokenWithType("a", 1, 37);
    token[33] = newTokenWithType("+", 1, 6);
    token[34] = newTokenWithType("b", 1, 37);
    token[35] = newTokenWithType(";", 1, 38);

    //END AddIntegers;
    token[36] = newTokenWithType("END", 3, 40);
    token[37] = newTokenWithType("AddIntegers", 11, 37);
    token[38] = newTokenWithType(";", 1, 38);

    //END TEST;
    token[39] = newTokenWithType("END", 3, 40);
    token[40] = newTokenWithType("TEST", 4, 37);
    token[41] = newTokenWithType(";", 1, 38);

    tokensflow->size = tokenSize;
    for (int i = 0; i < tokenSize; ++i)
        tokensflow->tokens[i] = token[i];

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
            if (tokensFlow.tokens[i].length != rightTokensFlow.tokens[i].length ||
                tokensFlow.tokens[i].type != rightTokensFlow.tokens[i].type)
                printf("Not equal type (number %d)", i);
            for (int j = 0; j < tokensFlow.tokens[i].length; ++j) {
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
    tf_printWithTypeTwoTokensFlow(tokensFlow, rightTokensFlow);

    printf("\n2 Test Result:\n");
    assertEquals(tokensFlow, rightTokensFlow);

}

