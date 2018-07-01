#include "../../Modules/Structures/A_Tokens.h"

//TOKEN


int test_token_newToken() {
    Token token;

    char symbols[] = "TOKEN";
    token = token_newToken("TOKEN", 5, 1);

    int checkSum = 0;
    for (int i = 0; i < token.length; ++i)
        if (token.symbols[i] == symbols[i])
            checkSum++;

    if (token.length == checkSum)
        return 1;
    return 0;
}

int test_token_newTokenWithType() {
    Token token;
    char symbols[] = "TOKEN";
    token = token_newTokenWithType("TOKEN", 5, 10, 1);

    int checkSum = 0;
    for (int i = 0; i < token.length; ++i)
        if (token.symbols[i] == symbols[i])
            checkSum++;

    if (token.length == checkSum && token.type == 10)
        return 1;
    return 0;
}

int test_token_equalsWithChar() {
    Token token = token_newTokenWithType("MOD", 3, 10, 1);
    if (!token_equalsWithString(token, "MOD", 3))
        return 0;
    return 1;

}

//TOKENSFLOW
int test_tf_initialize() {
    struct TokensFlow tokensFlow;
    tf_initialize(&tokensFlow);
    if (tokensFlow.size == 0 && tokensFlow.maxSize == TF_INIT_MAXSIZE)
        return 1;
    else return 0;
}

int test_tf_allocatedMemory() {
    struct TokensFlow tokensFlow;
    tf_initialize(&tokensFlow);
    tf_allocatedMemory(&tokensFlow);
    tf_allocatedMemory(&tokensFlow);
    tf_allocatedMemory(&tokensFlow);
    tf_allocatedMemory(&tokensFlow);

    if (tokensFlow.maxSize == 256)
        return 1;
    return 0;

}

int test_tf_addToken() {
    struct TokensFlow tokensFlow;
    tf_initialize(&tokensFlow);


    Token token0;
    token0 = token_newTokenWithType("MOD", 3, 10, 1);
    tf_addToken(&tokensFlow, &token0);
    if (!token_equals(tokensFlow.tokens[0], token0))
        return 0;


    for (int i = 0; i < TF_INIT_MAXSIZE * 8 + 1; ++i) {
        Token token;
        tf_addToken(&tokensFlow, &token);
    }

    if (tokensFlow.maxSize == 256 && tokensFlow.size == TF_INIT_MAXSIZE * 8 + 2)
        return 1;
    else return 0;

}

int test_tf_equals() {
    struct TokensFlow tokensFlow1;
    tf_initialize(&tokensFlow1);
    struct TokensFlow tokensFlow2;
    tf_initialize(&tokensFlow2);

    if (!tf_equals(tokensFlow1, tokensFlow2))
        return 0;

    for (int i = 0; i < 10; ++i) {
        Token token;
        token = token_newTokenWithType("MOD", 3, 10, 1);
        tf_addToken(&tokensFlow1, &token);
        tf_addToken(&tokensFlow2, &token);
    }
    if (tf_equals(tokensFlow1, tokensFlow2))
        return 1;
    return 0;
}


//
int main() {
    int rightTestDigit = 0;
    int maxTestDigit = 9;

    printf("Token Testing...\n\n");

    printf("token_allocatedMemory...\n");

    printf("token_newToken...\n");
    if (test_token_newToken() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("token_newTokenWithType...\n");
    if (test_token_newTokenWithType() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("token_equalsWithString...\n");
    if (test_token_newTokenWithType() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("TokensFlow Testing...\n\n");

    printf("tf_initialize...\n");
    if (test_tf_initialize() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("tf_allocatedMemory...\n");
    if (test_tf_allocatedMemory() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("tf_addToken...\n");
    if (test_tf_addToken() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("tf_equals...\n");
    if (test_tf_equals() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");

    return 0;
}