#ifndef OBERONSCOMPILER_A_TOKENS_H
#include "C_DeclaredVariables.h"
#define OBERONSCOMPILER_A_TOKENS_H


//__________________________________________________________________________________________________
const int TOKEN_INIT_MAXSIZE = 8;


struct Token {
    //int numberOfLine;//Для информации об ошибках
    int type;//Тип токена {n,t}
    int maxSize;
    int size;
    char *symbols;
};

void token_allocatedMemory(struct Token *token);

void token_initialize(struct Token *token);


void token_addSymbol(struct Token *token, char symbol);

struct Token token_newToken(char symbols[], int size);

struct Token token_newTokenWithType(char symbols[], int size, int type);

int token_equals(struct Token token1, struct Token token2);

//__________________________________________________________________________________________________

int TF_INIT_MAXSIZE = 16;

struct TokensFlow {
    struct DeclaredVariables declaredVariables;
    struct Token *tokens;
    int maxSize;
    int size;
    int pointer;
};

void tf_initialize(struct TokensFlow *tokensFlow);

void tf_allocatedMemory(struct TokensFlow *tokensFlow);

void tf_addToken(struct TokensFlow *tokensFlow, struct Token *token);

struct Token tf_next(struct TokensFlow *tokensFlow);

void tf_print(struct TokensFlow tokensFlow);

void tf_printWithType(struct TokensFlow tokensFlow);

int tf_equals(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo);
//__________________________________________________________________________________________________

#endif //OBERONSCOMPILER_A_TOKENS_H
