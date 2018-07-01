#include "../../Modules/B_LexAnalyzer.h"

char adress[] = "../Tests/ProgrammsOnOberon/1_Test.txt";


struct TokensFlow rightTokensFlow;

void createRightResultForFirstTest(struct TokensFlow *tokensflow) {
    Token token[50];
    int tokenSize = 42;

    // /MODULE TEST;
    token[0] = token_newTokenWithType("MODULE", 6, 63, 1);
    token[1] = token_newTokenWithType("TEST", 4, 37, 1);
    token[2] = token_newTokenWithType(";", 1, 38, 1);

    //CONST IntConst = 16;
    token[3] = token_newTokenWithType("CONST", 5, 57, 2);
    token[4] = token_newTokenWithType("IntConst", 8, 37, 2);
    token[5] = token_newTokenWithType("=", 1, 9, 2);
    token[6] = token_newTokenWithType("16", 2, 34, 2);
    token[7] = token_newTokenWithType(";", 1, 38, 2);

    //VARIABLE sum: INT;
    token[8] = token_newTokenWithType("VARIABLE", 3, 59, 3);
    token[9] = token_newTokenWithType("sum", 3, 37, 3);
    token[10] = token_newTokenWithType(":", 1, 20, 3);
    token[11] = token_newTokenWithType("INT", 7, 58, 3);
    token[12] = token_newTokenWithType(";", 1, 38, 3);

    //BoolVar: BOOLE;
    token[13] = token_newTokenWithType("BoolVar", 7, 37, 4);
    token[14] = token_newTokenWithType(":", 1, 20, 4);
    token[15] = token_newTokenWithType("BOOLEAN", 7, 58, 4);
    token[16] = token_newTokenWithType(";", 1, 38, 4);


    //PROCEDURE AddIntegers(a: INT; b: INT);
    token[17] = token_newTokenWithType("PROCEDURE", 9, 60, 5);
    token[18] = token_newTokenWithType("AddIntegers", 11, 37, 5);
    token[19] = token_newTokenWithType("(", 1, 29, 5);
    token[20] = token_newTokenWithType("a", 1, 37, 5);
    token[21] = token_newTokenWithType(":", 1, 20, 5);
    token[22] = token_newTokenWithType("INT", 7, 58, 5);
    token[23] = token_newTokenWithType(";", 1, 38, 5);
    token[24] = token_newTokenWithType("b", 1, 37, 5);
    token[25] = token_newTokenWithType(":", 1, 20, 5);
    token[26] = token_newTokenWithType("INT", 7, 58, 5);
    token[27] = token_newTokenWithType(")", 1, 22, 5);
    token[28] = token_newTokenWithType(";", 1, 38, 5);

    //BEGIN
    token[29] = token_newTokenWithType("BEGIN", 5, 61, 6);

    //sum := a + b;
    token[30] = token_newTokenWithType("sum", 3, 37, 7);
    token[31] = token_newTokenWithType(":=", 2, 33, 7);
    token[32] = token_newTokenWithType("a", 1, 37, 7);
    token[33] = token_newTokenWithType("+", 1, 6, 7);
    token[34] = token_newTokenWithType("b", 1, 37, 7);
    token[35] = token_newTokenWithType(";", 1, 38, 7);

    //END AddIntegers;
    token[36] = token_newTokenWithType("END", 3, 40, 8);
    token[37] = token_newTokenWithType("AddIntegers", 11, 37, 8);
    token[38] = token_newTokenWithType(";", 1, 38, 8);

    //END TEST;
    token[39] = token_newTokenWithType("END", 3, 40, 9);
    token[40] = token_newTokenWithType("TEST", 4, 37, 9);
    token[41] = token_newTokenWithType(";", 1, 38, 9);

    for (int i = 0; i < tokenSize; ++i) {
        tf_addToken(&rightTokensFlow, &token[i]);
    }

}

void tf_assertEquals(struct TokensFlow tokensFlow, struct TokensFlow rightTokensFlow) {
    int result = tf_equals(tokensFlow, rightTokensFlow);
    if (result == 1)
        printf("True\n");
    else if (result == 0) {
        printf("False\n");
        if (tokensFlow.size != rightTokensFlow.size)
            printf("Not equal size of TokensFlow\n");
        for (int i = 0; i < rightTokensFlow.size; ++i) {
            if (tokensFlow.tokens[i].size != rightTokensFlow.tokens[i].size ||
                tokensFlow.tokens[i].type != rightTokensFlow.tokens[i].type)
                printf("Not equal type (number %d)\n", i);
            for (int j = 0; j < tokensFlow.tokens[i].size; ++j) {
                if (tokensFlow.tokens[i].symbols[j] != rightTokensFlow.tokens[i].symbols[j])
                    printf("Not equal name(number %d letter %d\n", i, j);
            }
        }

    }

}


void tf_printWithTypeTwoTokensFlow(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo) {
    for (int i = 0; i < tokensFlowOne.size; ++i) {
        for (int j = 0; j < tokensFlowOne.tokens[i].size; ++j) {
            printf("%c", tokensFlowOne.tokens[i].symbols[j]);
        }
        printf("\t\t\ttype : %d\t\t", tokensFlowOne.tokens[i].type);

        for (int j = 0; j < tokensFlowTwo.tokens[i].size; ++j) {
            printf("%c", tokensFlowTwo.tokens[i].symbols[j]);
        }
        printf("\t\t\t\ttype : %d\n", tokensFlowTwo.tokens[i].type);

    }
}

int main() {

    tf_initialize(&rightTokensFlow);

    createRightResultForFirstTest(&rightTokensFlow);

    lexAnalysis(adress);


    printf("TF1\t\t\t\t\t\tTF2\t\n\n");
    tf_printWithTypeTwoTokensFlow(tokensFlow, rightTokensFlow);

    printf("\n2 Test Result:\n");
    printf("Compare TokensFlows\n");
    tf_assertEquals(tokensFlow, rightTokensFlow);

}

