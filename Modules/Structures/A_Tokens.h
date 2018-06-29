#ifndef OBERONSCOMPILER_A_TOKENS_H
#define OBERONSCOMPILER_A_TOKENS_H

#include "B_TerminalSymbols.h"

//__________________________________________________________________________________________________
const int TOKEN_INIT_MAXSIZE;


typedef struct token {
    int line; // line in source code
    int type; // probably deprecated
    int maxSize; //
    int size;
    char *symbols;
} Token;

void token_allocatedMemory(Token *token);

void token_initialize(Token *token);

void token_addSymbol(Token *token, char symbol);

Token token_newToken(char symbols[], int size, int numberOfLine);

Token token_newTokenWithType(char symbols[], int size, int type);

int token_equals(Token token1, Token token2);

int token_equalsWithString(Token token, const char *name);

char token_getName(Token token);

int token_defineType(Token token, struct TerminalSymbols terminalSymbols);

//__________________________________________________________________________________________________

const int TF_INIT_MAXSIZE;

struct TokensFlow {
    Token *tokens;
    int maxSize;
    int size;
    Token *current;
    int pointer;
};

void tf_initialize(struct TokensFlow *tokensFlow);

void tf_allocatedMemory(struct TokensFlow *tokensFlow);

void tf_addToken(struct TokensFlow *tokensFlow, Token *token);

Token* tf_next(struct TokensFlow *tokensFlow);

void tf_print(struct TokensFlow tokensFlow);

void tf_printWithType(struct TokensFlow tokensFlow);

int tf_equals(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo);
//__________________________________________________________________________________________________

#endif //OBERONSCOMPILER_A_TOKENS_H
