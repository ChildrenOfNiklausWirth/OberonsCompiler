#include "../../Modules/B_LexAnalyzer.h"
#include "../../Modules/Structures/A_Tokens.h"

enum PrintOfTokensFlow {
    PRINT, NO_PRINT
};

char firstAdress[] = "../Tests/ProgrammsOnOberon/1_Test.txt";
char secondAdress[] = "../Tests/ProgrammsOnOberon/2_Test.txt";

void createRightResultForFirstTest(struct TokensFlow *tokensflow) {
    Token tokens[42];
    int tokensSize = 42;

    // /MODULE TEST;
    tokens[0] = token_newTokenWithType("MODULE", 6, 63, 1);
    tokens[1] = token_newTokenWithType("TEST", 4, 37, 1);
    tokens[2] = token_newTokenWithType(";", 1, 38, 1);

    //CONST IntConst = 16;
    tokens[3] = token_newTokenWithType("CONST", 5, 57, 2);
    tokens[4] = token_newTokenWithType("IntConst", 8, 37, 2);
    tokens[5] = token_newTokenWithType("=", 1, 9, 2);
    tokens[6] = token_newTokenWithType("16", 2, 34, 2);
    tokens[7] = token_newTokenWithType(";", 1, 38, 2);

    //VAR sum: INTEGER;
    tokens[8] = token_newTokenWithType("VAR", 3, 59, 3);
    tokens[9] = token_newTokenWithType("sum", 3, 37, 3);
    tokens[10] = token_newTokenWithType(":", 1, 20, 3);
    tokens[11] = token_newTokenWithType("INTEGER", 7, 58, 3);
    tokens[12] = token_newTokenWithType(";", 1, 38, 3);

    //BoolVar: BOOLE;
    tokens[13] = token_newTokenWithType("BoolVar", 7, 37, 4);
    tokens[14] = token_newTokenWithType(":", 1, 20, 4);
    tokens[15] = token_newTokenWithType("BOOLEAN", 7, 58, 4);
    tokens[16] = token_newTokenWithType(";", 1, 38, 4);


    //PROCEDURE AddIntegers(a: INTEGER; b: INTEGER);
    tokens[17] = token_newTokenWithType("PROCEDURE", 9, 60, 5);
    tokens[18] = token_newTokenWithType("AddIntegers", 11, 37, 5);
    tokens[19] = token_newTokenWithType("(", 1, 29, 5);
    tokens[20] = token_newTokenWithType("a", 1, 37, 5);
    tokens[21] = token_newTokenWithType(":", 1, 20, 5);
    tokens[22] = token_newTokenWithType("INTEGER", 7, 58, 5);
    tokens[23] = token_newTokenWithType(";", 1, 38, 5);
    tokens[24] = token_newTokenWithType("b", 1, 37, 5);
    tokens[25] = token_newTokenWithType(":", 1, 20, 5);
    tokens[26] = token_newTokenWithType("INTEGER", 7, 58, 5);
    tokens[27] = token_newTokenWithType(")", 1, 22, 5);
    tokens[28] = token_newTokenWithType(";", 1, 38, 5);

    //BEGIN
    tokens[29] = token_newTokenWithType("BEGIN", 5, 61, 6);

    //sum := a + b;
    tokens[30] = token_newTokenWithType("sum", 3, 37, 7);
    tokens[31] = token_newTokenWithType(":=", 2, 33, 7);
    tokens[32] = token_newTokenWithType("a", 1, 37, 7);
    tokens[33] = token_newTokenWithType("+", 1, 6, 7);
    tokens[34] = token_newTokenWithType("b", 1, 37, 7);
    tokens[35] = token_newTokenWithType(";", 1, 38, 7);

    //END AddIntegers;
    tokens[36] = token_newTokenWithType("END", 3, 40, 8);
    tokens[37] = token_newTokenWithType("AddIntegers", 11, 37, 8);
    tokens[38] = token_newTokenWithType(";", 1, 38, 8);

    //END TEST;
    tokens[39] = token_newTokenWithType("END", 3, 40, 9);
    tokens[40] = token_newTokenWithType("TEST", 4, 37, 9);
    tokens[41] = token_newTokenWithType(";", 1, 38, 9);

    for (int i = 0; i < tokensSize; ++i)
        tf_addToken(tokensflow, &tokens[i]);

    if (tokensflow->size != tokensSize)
        printf("Problems with TokensFlow");


}

void createRightResultForSecondTest(struct TokensFlow *tokensflow) {
    Token tokens[44];
    int tokenSize = 44;
    tokens[0] = token_newTokenWithType("NULL", 4, 0, 1);
    tokens[1] = token_newTokenWithType("*", 1, 1, 2);
    tokens[2] = token_newTokenWithType("/", 1, 3, 3);
    tokens[3] = token_newTokenWithType("MOD", 3, 4, 4);
    tokens[4] = token_newTokenWithType("AND", 3, 5, 5);
    tokens[5] = token_newTokenWithType("+", 1, 6, 6);
    tokens[6] = token_newTokenWithType("-", 1, 7, 7);
    tokens[7] = token_newTokenWithType("&", 1, 8, 8);
    tokens[8] = token_newTokenWithType("=", 1, 9, 9);
    tokens[9] = token_newTokenWithType("#", 1, 10, 10);
    tokens[10] = token_newTokenWithType("<", 1, 11, 11);
    tokens[11] = token_newTokenWithType(">=", 2, 12, 12);
    tokens[12] = token_newTokenWithType("<=", 2, 13, 13);
    tokens[13] = token_newTokenWithType(">", 1, 14, 14);
    tokens[14] = token_newTokenWithType(".", 1, 18, 15);
    tokens[15] = token_newTokenWithType(",", 1, 19, 16);
    tokens[16] = token_newTokenWithType(":", 1, 20, 17);
    tokens[17] = token_newTokenWithType(")", 1, 22, 18);
    tokens[18] = token_newTokenWithType("]", 1, 23, 19);
    tokens[19] = token_newTokenWithType("OF", 2, 25, 20);
    tokens[20] = token_newTokenWithType("THEN", 4, 26, 21);
    tokens[21] = token_newTokenWithType("DO", 2, 27, 22);
    tokens[22] = token_newTokenWithType("(", 1, 29, 23);
    tokens[23] = token_newTokenWithType("[", 1, 30, 24);
    tokens[24] = token_newTokenWithType("`", 1, 32, 25);
    tokens[25] = token_newTokenWithType(":=", 2, 33, 26);
    tokens[26] = token_newTokenWithType("2134", 4, 34, 27);
    tokens[27] = token_newTokenWithType("ident", 5, 37, 28);
    tokens[28] = token_newTokenWithType(";", 1, 38, 29);
    tokens[29] = token_newTokenWithType("END", 3, 40, 29);
    tokens[30] = token_newTokenWithType("ELSE", 4, 41, 30);
    tokens[31] = token_newTokenWithType("ELSEIF", 6, 42, 31);
    tokens[32] = token_newTokenWithType("IF", 2, 44, 32);
    tokens[33] = token_newTokenWithType("WHILE", 5, 46, 33);
    tokens[34] = token_newTokenWithType("ARRAY", 5, 54, 34);
    tokens[35] = token_newTokenWithType("RECORD", 6, 55, 35);
    tokens[36] = token_newTokenWithType("CONST", 5, 57, 36);
    tokens[37] = token_newTokenWithType("INTEGER", 7, 58, 37);
    tokens[38] = token_newTokenWithType("BOOLEAN", 7, 58, 38);
    tokens[39] = token_newTokenWithType("VAR", 3, 59, 39);
    tokens[40] = token_newTokenWithType("PROCEDURE", 9, 60, 40);
    tokens[41] = token_newTokenWithType("BEGIN", 5, 61, 41);
    tokens[42] = token_newTokenWithType("MODULE", 6, 63, 42);
    tokens[43] = token_newTokenWithType("EOF", 3, 64, 43);

    tf_clear(tokensflow);
    tf_initialize(tokensflow);

    for (int i = 0; i < tokenSize; ++i)
        tf_addToken(tokensflow, &tokens[i]);

    if (tokensflow->size != tokenSize)
        printf("Problems with TokensFlow");

}

void tf_assertEqualsTwoTokensFlows(struct TokensFlow tokensFlow, struct TokensFlow rightTokensFlow) {
    int result = tf_equals(tokensFlow, rightTokensFlow);
    if (result == 1)
        printf("True\n");
    else if (result == 0) {
        printf("False\n");
        if (tokensFlow.size != rightTokensFlow.size)
            printf("Not equal size of TokensFlow\nsyntaxTokensFlow=%d\t rightTokensFlow=%d\n", tokensFlow.size,
                   rightTokensFlow.size);

        for (int i = 0; i < rightTokensFlow.size; ++i) {
            if (tokensFlow.tokens[i].length != rightTokensFlow.tokens[i].length ||
                tokensFlow.tokens[i].type != rightTokensFlow.tokens[i].type) {
                printf("Not equal type\n");
                token_print(tokensFlow.tokens[i]);
                token_print(rightTokensFlow.tokens[i]);
            }
            for (int j = 0; j < tokensFlow.tokens[i].length; ++j) {
                if (tokensFlow.tokens[i].symbols[j] != rightTokensFlow.tokens[i].symbols[j]) {
                    printf("Not equal name)\n");
                    token_print(tokensFlow.tokens[i]);
                    token_print(rightTokensFlow.tokens[i]);
                }
            }
        }

    }

}

void tf_printWithTypeTwoTokensFlow(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo) {
    for (int i = 0; i < tokensFlowOne.size; ++i) {
        for (int j = 0; j < tokensFlowOne.tokens[i].length; ++j) {
            printf("%c", tokensFlowOne.tokens[i].symbols[j]);
        }
        printf("\t\t\ttype : %d\t\t", tokensFlowOne.tokens[i].type);

        for (int j = 0; j < tokensFlowTwo.tokens[i].length; ++j) {
            printf("%c", tokensFlowTwo.tokens[i].symbols[j]);
        }
        printf("\t\t\t\ttype : %d\n", tokensFlowTwo.tokens[i].type);

    }
}

//__________________________________________________________________________________________________
void firstTest(enum PrintOfTokensFlow print) {

    struct TokensFlow rightTokensFlow;
    tf_initialize(&rightTokensFlow);
    createRightResultForFirstTest(&rightTokensFlow);

    lexAnalysis(firstAdress);


    if (print == PRINT) {
        printf("SYNTAX\t\t\t\t\t\tRIGHT RESULT\t\n\n");
        tf_printWithTypeTwoTokensFlow(syntaxTokensFlow, rightTokensFlow);
        printf("\n\n\n");
    }

    printf("1 Test Result:\n");
    tf_assertEqualsTwoTokensFlows(syntaxTokensFlow, rightTokensFlow);
    tf_clear(&syntaxTokensFlow);

}

void secondTest(enum PrintOfTokensFlow print) {
    struct TokensFlow rightTokensFlow;
    tf_initialize(&rightTokensFlow);
    createRightResultForSecondTest(&rightTokensFlow);

    lexAnalysis(secondAdress);

    if (print == PRINT) {
        printf("SYNTAX\t\t\t\t\t\tRIGHT RESULT\t\n\n");
        tf_printWithTypeTwoTokensFlow(syntaxTokensFlow, rightTokensFlow);
        printf("\n\n\n");
    }

    printf("2 Test Result:\n");
    tf_assertEqualsTwoTokensFlows(syntaxTokensFlow, rightTokensFlow);
    tf_clear(&syntaxTokensFlow);

}
//__________________________________________________________________________________________________

int main() {
    printf("-----------------------------------1 TEST-------------------------------------------------------\n");
    firstTest(NO_PRINT);
    printf("-----------------------------------2 TEST-------------------------------------------------------\n");
    secondTest(NO_PRINT);
    printf("------------------------------------------------------------------------------------------------");
}

