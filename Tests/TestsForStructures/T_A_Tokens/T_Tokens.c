#include "../../../Modules/Structures/A_Tokens_And_DV.c"

//TOKEN
int test_token_allocatedMemory() {
    struct Token token;
    token = token_newToken("TOKEN", 5);
    token_allocatedMemory(&token);
    if (token.maxSize == TOKEN_INIT_MAXSIZE * 2)
        return 1;
    else return 0;

}

int test_token_addSymbol() {
    struct Token token;
    for (int i = 0; i < TOKEN_INIT_MAXSIZE; ++i)
        if (i % 2 == 0)
            token_addSymbol(&token, 'M');
        else
            token_addSymbol(&token, 'N');

    for (int j = 0; j < token.size;) {
        if (!(token.symbols[j] == 'M' && token.symbols[j + 1] == 'N'))
            return 0;
        j += 2;
    }
    if (!(token.size == TOKEN_INIT_MAXSIZE && token.maxSize == TOKEN_INIT_MAXSIZE * 2))
        return 0;


    return 1;
}

int test_token_newToken() {
    struct Token token;

    char symbols[] = "TOKEN";
    token = token_newToken("TOKEN", 5);

    int checkSum = 0;
    for (int i = 0; i < token.size; ++i)
        if (token.symbols[i] == symbols[i])
            checkSum++;

    if (token.size == checkSum && token.maxSize == TOKEN_INIT_MAXSIZE)
        return 1;
    return 0;
}

int test_token_newTokenWithType() {
    struct Token token;

    char symbols[] = "TOKEN";
    token = token_newTokenWithType("TOKEN", 5, 10);

    int checkSum = 0;
    for (int i = 0; i < token.size; ++i)
        if (token.symbols[i] == symbols[i])
            checkSum++;

    if (token.size == checkSum && token.maxSize == TOKEN_INIT_MAXSIZE && token.type == 10)
        return 1;
    return 0;
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


    struct Token token0;
    token0 = token_newTokenWithType("MOD", 3, 10);
    tf_addToken(&tokensFlow, &token0);
    if (!token_equals(tokensFlow.tokens[0], token0))
        return 0;


    for (int i = 0; i < TF_INIT_MAXSIZE * 8 + 1; ++i) {
        struct Token token;
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
        struct Token token;
        token=token_newTokenWithType("MOD",3,10);
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
    int maxTestDigit = 8;

    printf("Token Testing...\n\n");

    printf("token_allocatedMemory...\n");
    if (test_token_allocatedMemory() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

    printf("token_addSymbol...\n");
    if (test_token_addSymbol() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");

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