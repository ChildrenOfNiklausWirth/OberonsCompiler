#include "../../Modules/B_LexAnalyzer.h"

char adress[] = "..\\Tests\\ProgrammsOnOberon\\1_Test.txt";

struct TokensFlow tokensFlow;
struct TokensFlow rightTokensFlow;
struct DeclaredVariables declaredVariables;
struct DeclaredVariables rightDeclaredVariables;

void createRightResultForFirstTest(struct TokensFlow *tokensflow, struct DeclaredVariables *rightDeclaredVariables) {
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

    //BoolVar: BOOLE;
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


    for (int i = 0; i < tokenSize; ++i) {
        tf_addToken(tokensflow, &token[i]);
        if (token[i].type == terminalSymbols.IDENT.type)
            dv_addVarialbe(rightDeclaredVariables, &token[i], terminalSymbols);
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

void dv_assertEqauls(struct DeclaredVariables declaredVariables, struct DeclaredVariables rightDeclaredVariables) {
    int result = dv_equals(declaredVariables, rightDeclaredVariables);
    if (result == 1)
        printf("True\n");
    else if (result == 0) {
        printf("False\n");
        if (declaredVariables.size != rightDeclaredVariables.size)
            printf("Not equal size of TokensFlow\n");
        for (int i = 0; i < rightTokensFlow.size; ++i) {
            if (declaredVariables.variables[i].nameLength != rightDeclaredVariables.variables[i].nameLength ||
                declaredVariables.variables[i].type != rightDeclaredVariables.variables[i].type)
                printf("Not equal type (number %d)\n", i);
            for (int j = 0; j < declaredVariables.variables[i].nameLength; ++j) {
                if (declaredVariables.variables[i].name[j] != rightDeclaredVariables.variables[i].name[j])
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

void dv_printWithTypeTwoDV(struct DeclaredVariables declaredVariablesOne, struct DeclaredVariables declaredVariablesTwo){
    for (int i = 0; i < declaredVariablesOne.size; ++i) {
        for (int j = 0; j < declaredVariablesOne.variables[i].nameLength; ++j) {
            printf("%c", declaredVariablesOne.variables[i].name[j]);
        }
        printf("\t\t\ttype : %d\t\t", declaredVariablesTwo.variables[i].type);

        for (int j = 0; j < declaredVariablesTwo.variables[i].nameLength; ++j) {
            printf("%c", declaredVariablesTwo.variables[i].name[j]);
        }
        printf("\t\t\t\ttype : %d\n", declaredVariablesTwo.variables[i].type);

    }
}

int main() {
    tf_initialize(&rightTokensFlow);
    dv_initialize(&declaredVariables);
    tss_initialize(&terminalSymbols);

    createRightResultForFirstTest(&rightTokensFlow, &rightDeclaredVariables);

    lexAnalysis(adress, &tokensFlow, &declaredVariables);


    printf("\nDV1\t\t\t\t\t\tDV2\t\n\n");
    dv_printWithTypeTwoDV(declaredVariables,rightDeclaredVariables);

    printf("\nTF1\t\t\t\t\t\tTF2\t\n\n");
    tf_printWithTypeTwoTokensFlow(tokensFlow, rightTokensFlow);
    printf("\n2 Test Result:\n");

    printf("Compare TokensFlows\n");
    tf_assertEquals(tokensFlow, rightTokensFlow);
    printf("\nCompare DeclaredVariables\n");
    dv_assertEqauls(declaredVariables, rightDeclaredVariables);
}

