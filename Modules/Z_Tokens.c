#include <stdio.h>
#include <stdlib.h>
#include "X_DeclaredVariables.c"

//__________________________________________________________________________________________________
const int TOKEN_INIT_MAXSIZE = 8;

struct Token {
    //int numberOfLine;//Для информации об ошибках
    int type;//Тип токена {n,t}
    int maxSize;
    int size;
    char *symbols;
};

void token_allocatedMemory(struct Token *token) {
    token->maxSize = token->maxSize * 2;
    token->symbols = realloc(token->symbols, sizeof(struct Token) * token->maxSize);
}

void token_initialize(struct Token *token) {
    token->maxSize = TOKEN_INIT_MAXSIZE;
    token->symbols = malloc(sizeof(char) * TOKEN_INIT_MAXSIZE);
    token->size = 0;
}

void token_addSymbol(struct Token *token, char symbol) {
    if (token->maxSize == 0)
        token_initialize(token);
    if (token->size == token->maxSize - 1)
        token_allocatedMemory(token);
    token->symbols[token->size] = symbol;
    token->size = token->size + 1;

}

struct Token token_newToken(char symbols[], int size) {
    struct Token token;
    token.symbols = malloc(sizeof(char) * TOKEN_INIT_MAXSIZE);
    token.size = 0;
    token.maxSize = TOKEN_INIT_MAXSIZE;
    for (int i = 0; i < size; ++i)
        token_addSymbol(&token, symbols[i]);
    return token;
}

struct Token token_newTokenWithType(char symbols[], int size, int type) {
    struct Token token = token_newToken(symbols, size);
    token.type = type;
    return token;
}

int token_equals(struct Token token1, struct Token token2) {
    int equalDigit = 0;
    int paramsDigit = 4;
    if (token1.symbols == token2.symbols)
        equalDigit++;
    if (token1.size == token2.size)
        equalDigit++;
    if (token1.maxSize == token2.maxSize)
        equalDigit++;
    if (token1.type == token2.type)
        equalDigit++;
    if (equalDigit == paramsDigit)
        return 1;
    return 0;


}

//__________________________________________________________________________________________________

int TF_INIT_MAXSIZE = 16;

struct TokensFlow {
    struct DeclaredVariables declaredVariables;
    struct Token *tokens;
    int maxSize;
    int size;
    int pointer;
};


void tf_initialize(struct TokensFlow *tokensFlow) {
    dv_initialize(&tokensFlow->declaredVariables);
    tokensFlow->maxSize = TF_INIT_MAXSIZE;
    tokensFlow->tokens = malloc(sizeof(struct Token) * TF_INIT_MAXSIZE);
    tokensFlow->size = 0;
    tokensFlow->pointer = 0;
}

void tf_allocatedMemory(struct TokensFlow *tokensFlow) {
    tokensFlow->maxSize = tokensFlow->maxSize * 2;
    tokensFlow->tokens = realloc(tokensFlow->tokens, sizeof(struct Token) * tokensFlow->maxSize);
}

void tf_addToken(struct TokensFlow *tokensFlow, struct Token *token) {
    if (tokensFlow->maxSize == 0)
        tf_initialize(tokensFlow);
    if (tokensFlow->size == tokensFlow->maxSize - 1)
        tf_allocatedMemory(tokensFlow);
    if (token->type == 37)
        dv_addVarialbe(&tokensFlow->declaredVariables, token);
    tokensFlow->tokens[tokensFlow->size] = *token;
    tokensFlow->size++;
}

struct Token tf_next(struct TokensFlow *tokensFlow) {
    struct Token token = tokensFlow->tokens[tokensFlow->pointer];
    tokensFlow->pointer++;
    return token;
}

void tf_print(struct TokensFlow tokensFlow) {
    for (int i = 0; i < tokensFlow.size; ++i) {
        for (int j = 0; j < tokensFlow.tokens[i].size; ++j) {
            printf("%c", tokensFlow.tokens[i].symbols[j]);
        }
        printf("\n");

    }

}

void tf_printWithType(struct TokensFlow tokensFlow) {
    for (int i = 0; i < tokensFlow.size; ++i) {
        for (int j = 0; j < tokensFlow.tokens[i].size; ++j) {
            printf("%c", tokensFlow.tokens[i].symbols[j]);
        }
        printf("\t\ttype : %d\n", tokensFlow.tokens[i].type);
    }
}

int tf_equals(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo) {
    if (tokensFlowOne.size != tokensFlowTwo.size)
        return 0;
    for (int i = 0; i < tokensFlowOne.size; ++i) {

        if (tokensFlowOne.tokens[i].type != tokensFlowTwo.tokens[i].type)
            return 0;
        for (int j = 0; j < tokensFlowOne.tokens[i].size; ++j) {
            if (tokensFlowOne.tokens[i].symbols[j] != tokensFlowTwo.tokens[i].symbols[j])
                return 0;
        }
    }
    return 1;
}
//__________________________________________________________________________________________________