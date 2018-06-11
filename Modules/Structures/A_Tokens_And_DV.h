#ifndef OBERONSCOMPILER_A_TOKENS_H
#define OBERONSCOMPILER_A_TOKENS_H

#include "B_TerminalSymbols.h"

//__________________________________________________________________________________________________
const int TOKEN_INIT_MAXSIZE;


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

int token_equalsWithString(struct Token token, const char *name);

char token_getName(struct Token token);

int token_defineType(struct Token token, struct TerminalSymbols terminalSymbols);

//__________________________________________________________________________________________________
//TODO neccessary constant
const int V_MAX_NAMELENGTH;

enum TypesOfVariable {
    INTEG, BOOLE

};

struct Variable {
    char name[20];
    int nameLength;
    enum TypesOfVariable type;
};


void v_setName(struct Variable *variable, char name[], int nameLength);


void v_createFromToken(struct Variable *variable, struct Token *token, struct TerminalSymbols terminalSymbols);

//__________________________________________________________________________________________________

const int DV_INIT_MAXSIZE;

struct DeclaredVariables {
    struct Variable *variables;
    int maxSize;
    int size;
};

void dv_allocatedMemory(struct DeclaredVariables *declaredVariables);

void dv_initialize(struct DeclaredVariables *declaredVariables);

void dv_addVarialbe(struct DeclaredVariables *declaredVariables, struct Token *token,
                    struct TerminalSymbols terminalSymbols);

int dv_equals(struct DeclaredVariables declaredVariablesOne, struct DeclaredVariables declaredVariablesTwo);

//__________________________________________________________________________________________________

const int TF_INIT_MAXSIZE;

struct TokensFlow {
    struct Token *tokens;
    int maxSize;
    int size;
    struct Token currentToken;
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
