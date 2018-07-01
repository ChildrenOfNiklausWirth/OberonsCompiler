#ifndef OBERONSCOMPILER_A_TOKENS_H
#define OBERONSCOMPILER_A_TOKENS_H

#include "B_TerminalSymbols.h"


typedef struct {
    int nameLength;
    char *name;
} Ident;

Ident ident_new(char name[], int nameLength);

//__________________________________________________________________________________________________
typedef struct {
    int line; // line in source code
    int type; // probably deprecated
    int length;
    char *symbols;
} Token;


void token_initialize(Token *token, int nameLength);

Token token_newToken(char symbols[], int nameLength, int numberOfLine);

Token token_newTokenWithType(char symbols[], int nameLength, int type, int numberOfLine);

int token_equals(Token token1, Token token2);

int token_equalsWithString(Token token, const char str[], int strLength);

void token_print(Token token);

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

Token *tf_next(struct TokensFlow *tokensFlow);

void tf_clear(struct TokensFlow *tokensFlow);

void tf_print(struct TokensFlow tokensFlow);

void tf_printWithType(struct TokensFlow tokensFlow);

int tf_equals(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo);
//__________________________________________________________________________________________________

#endif //OBERONSCOMPILER_A_TOKENS_H