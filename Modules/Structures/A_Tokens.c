#include <stdio.h>
#include <stdlib.h>
#include "A_Tokens.h"

Ident *ident_new(char name[], int nameLength) {
    Ident *ident;
    ident = calloc(1, sizeof(ident));
    ident->name = malloc(sizeof(char) * nameLength);
    for (int i = 0; i < nameLength; ++i)
        ident->name[i] = name[i];
    return ident;
}

//__________________________________________________________________________________________________
void token_initialize(Token *token, int nameLength) {
    token->symbols = malloc(sizeof(char) * nameLength);
    token->length = nameLength;
    token->type = 0;
}

Token token_newToken(char symbols[], int nameLength, int numberOfLine) {
    Token token;
    token.symbols = malloc(sizeof(char) * nameLength);
    token.length = nameLength;
    token.line = numberOfLine;
    for (int i = 0; i < nameLength; ++i)
        token.symbols[i] = symbols[i];
    return token;
}

Token token_newTokenWithType(char symbols[], int nameLength, int type, int numberOfLine) {
    Token token = token_newToken(symbols, nameLength, numberOfLine);
    token.type = type;
    return token;
}

int token_equals(Token token1, Token token2) {
    if (token1.symbols != token2.symbols)
        return 0;
    if (token1.length != token2.length)
        return 0;
    if (token1.type != token2.type)
        return 0;
    return 1;


}

int token_equalsWithString(Token token, const char str[], int strLength) {
    if (token.length != strLength)
        return 0;

    for (int i = 0; i < token.length; ++i)
        if (token.symbols[i] != str[i])
            return 0;

    return 1;
}

void token_print(Token token) {
    for (int i = 0; i < token.length; ++i)
        printf("%c", token.symbols[i]);
    printf("\n");
}

int token_defineType(Token token, struct TerminalSymbols terminalSymbols) {
    if (token_equalsWithString(token, terminalSymbols.NULLL.name, terminalSymbols.NULLL.nameLength))
        return terminalSymbols.NULLL.type;
    if (token_equalsWithString(token, terminalSymbols.TIMES.name, terminalSymbols.TIMES.nameLength))
        return terminalSymbols.TIMES.type;
    if (token_equalsWithString(token, terminalSymbols.DIV.name, terminalSymbols.DIV.nameLength))
        return terminalSymbols.DIV.type;
    if (token_equalsWithString(token, terminalSymbols.MOD.name, terminalSymbols.MOD.nameLength))
        return terminalSymbols.MOD.type;
    if (token_equalsWithString(token, terminalSymbols.AND.name, terminalSymbols.AND.nameLength))
        return terminalSymbols.AND.type;
    if (token_equalsWithString(token, terminalSymbols.PLUS.name, terminalSymbols.PLUS.nameLength))
        return terminalSymbols.PLUS.type;
    if (token_equalsWithString(token, terminalSymbols.MINUS.name, terminalSymbols.MINUS.nameLength))
        return terminalSymbols.MINUS.type;
    if (token_equalsWithString(token, terminalSymbols.OR.name, terminalSymbols.OR.nameLength))
        return terminalSymbols.OR.type;
    if (token_equalsWithString(token, terminalSymbols.EQL.name, terminalSymbols.EQL.nameLength))
        return terminalSymbols.EQL.type;
    if (token_equalsWithString(token, terminalSymbols.NEQ.name, terminalSymbols.NEQ.nameLength))
        return terminalSymbols.NEQ.type;
    if (token_equalsWithString(token, terminalSymbols.LSS.name, terminalSymbols.LSS.nameLength))
        return terminalSymbols.LSS.type;
    if (token_equalsWithString(token, terminalSymbols.GEQ.name, terminalSymbols.GEQ.nameLength))
        return terminalSymbols.GEQ.type;
    if (token_equalsWithString(token, terminalSymbols.LEQ.name, terminalSymbols.LEQ.nameLength))
        return terminalSymbols.LEQ.type;
    if (token_equalsWithString(token, terminalSymbols.GTR.name, terminalSymbols.GTR.nameLength))
        return terminalSymbols.GTR.type;
    if (token_equalsWithString(token, terminalSymbols.PERIOD.name, terminalSymbols.PERIOD.nameLength))
        return terminalSymbols.PERIOD.type;
    if (token_equalsWithString(token, terminalSymbols.COMMA.name, terminalSymbols.COMMA.nameLength))
        return terminalSymbols.COMMA.type;
    if (token_equalsWithString(token, terminalSymbols.COLON.name, terminalSymbols.COLON.nameLength))
        return terminalSymbols.COLON.type;
    if (token_equalsWithString(token, terminalSymbols.RPAREN.name, terminalSymbols.RPAREN.nameLength))
        return terminalSymbols.RPAREN.type;
    if (token_equalsWithString(token, terminalSymbols.RBRAK.name, terminalSymbols.RBRAK.nameLength))
        return terminalSymbols.RBRAK.type;
    if (token_equalsWithString(token, terminalSymbols.OF.name, terminalSymbols.OF.nameLength))
        return terminalSymbols.OF.type;
    if (token_equalsWithString(token, terminalSymbols.THEN.name, terminalSymbols.THEN.nameLength))
        return terminalSymbols.THEN.type;
    if (token_equalsWithString(token, terminalSymbols.DO.name, terminalSymbols.DO.nameLength))
        return terminalSymbols.DO.type;
    if (token_equalsWithString(token, terminalSymbols.LPAREN.name, terminalSymbols.LPAREN.nameLength))
        return terminalSymbols.LPAREN.type;
    if (token_equalsWithString(token, terminalSymbols.LBRAK.name, terminalSymbols.LBRAK.nameLength))
        return terminalSymbols.LBRAK.type;
    if (token_equalsWithString(token, terminalSymbols.NOT.name, terminalSymbols.NOT.nameLength))
        return terminalSymbols.NOT.type;
    if (token_equalsWithString(token, terminalSymbols.BECOMES.name, terminalSymbols.BECOMES.nameLength))
        return terminalSymbols.BECOMES.type;
    if (token_equalsWithString(token, terminalSymbols.NUMBER.name, terminalSymbols.NUMBER.nameLength))
        return terminalSymbols.NUMBER.type;
    if (token_equalsWithString(token, terminalSymbols.IDENT.name, terminalSymbols.IDENT.nameLength))
        return terminalSymbols.IDENT.type;
    if (token_equalsWithString(token, terminalSymbols.SEMICOLON.name, terminalSymbols.SEMICOLON.nameLength))
        return terminalSymbols.SEMICOLON.type;
    if (token_equalsWithString(token, terminalSymbols.END.name, terminalSymbols.END.nameLength))
        return terminalSymbols.END.type;
    if (token_equalsWithString(token, terminalSymbols.ELSE.name, terminalSymbols.ELSE.nameLength))
        return terminalSymbols.ELSE.type;
    if (token_equalsWithString(token, terminalSymbols.ELSEIF.name, terminalSymbols.ELSEIF.nameLength))
        return terminalSymbols.ELSEIF.type;
    if (token_equalsWithString(token, terminalSymbols.IF.name, terminalSymbols.IF.nameLength))
        return terminalSymbols.IF.type;
    if (token_equalsWithString(token, terminalSymbols.WHILE.name, terminalSymbols.WHILE.nameLength))
        return terminalSymbols.WHILE.type;
    if (token_equalsWithString(token, terminalSymbols.ARR.name, terminalSymbols.ARR.nameLength))
        return terminalSymbols.ARR.type;
    if (token_equalsWithString(token, terminalSymbols.REC.name, terminalSymbols.REC.nameLength))
        return terminalSymbols.REC.type;
    if (token_equalsWithString(token, terminalSymbols.CONSTT.name, terminalSymbols.CONSTT.nameLength))
        if (token_equalsWithString(token, terminalSymbols.ARR.name, terminalSymbols.ARR.nameLength))
            return terminalSymbols.ARR.type;
    if (token_equalsWithString(token, terminalSymbols.REC.name, terminalSymbols.REC.nameLength))
        return terminalSymbols.REC.type;
    if (token_equalsWithString(token, terminalSymbols.CONSTT.name, terminalSymbols.CONSTT.nameLength))
        return terminalSymbols.CONSTT.type;
    if (token_equalsWithString(token, terminalSymbols.TYPE.name, terminalSymbols.TYPE.nameLength))
        return terminalSymbols.TYPE.type;
    if (token_equalsWithString(token, terminalSymbols.VAR.name, terminalSymbols.VAR.nameLength))
        return terminalSymbols.VAR.type;
    if (token_equalsWithString(token, terminalSymbols.PROCEDURE.name, terminalSymbols.PROCEDURE.nameLength))
        return terminalSymbols.PROCEDURE.type;
    if (token_equalsWithString(token, terminalSymbols.BEGIN.name, terminalSymbols.BEGIN.nameLength))
        return terminalSymbols.BEGIN.type;
    if (token_equalsWithString(token, terminalSymbols.MODULE.name, terminalSymbols.MODULE.nameLength))
        return terminalSymbols.MODULE.type;
    if (token_equalsWithString(token, terminalSymbols.TYPE.name, terminalSymbols.TYPE.nameLength))
        return terminalSymbols.TYPE.type;
    if (token_equalsWithString(token, terminalSymbols.EOFF.name, terminalSymbols.EOFF.nameLength))
        return terminalSymbols.EOFF.type;

    int sum = 0;
    for (int k = 0; k < token.length; ++k)
        if (charIsDigit(token.symbols[k]))
            sum++;
        else break;

    if (sum == token.length)
        return terminalSymbols.NUMBER.type;


    return terminalSymbols.IDENT.type;

}

//__________________________________________________________________________________________________

const int TF_INIT_MAXSIZE = 16;

void tf_initialize(struct TokensFlow *tokensFlow) {
    tokensFlow->maxSize = TF_INIT_MAXSIZE;
    tokensFlow->tokens = malloc(sizeof(Token) * TF_INIT_MAXSIZE);
    tokensFlow->size = 0;
    tokensFlow->pointer = 0;
}

void tf_allocatedMemory(struct TokensFlow *tokensFlow) {
    tokensFlow->maxSize = tokensFlow->maxSize + 10;
    tokensFlow->tokens = realloc(tokensFlow->tokens, sizeof(Token) * tokensFlow->maxSize);
}

void tf_addToken(struct TokensFlow *tokensFlow, Token *token) {
    if (tokensFlow->maxSize == 0)
        tf_initialize(tokensFlow);
    if (tokensFlow->size == tokensFlow->maxSize - 1)
        tf_allocatedMemory(tokensFlow);
    tokensFlow->tokens[tokensFlow->size] = *token;
    tokensFlow->size++;
}

Token *tf_next(struct TokensFlow *tokensFlow) {
    tokensFlow->current = &tokensFlow->tokens[tokensFlow->pointer];
    tokensFlow->pointer++;
    return tokensFlow->current;
}

void tf_clear(struct TokensFlow *tokensFlow) {
    free(tokensFlow->tokens);
    tokensFlow->size = 0;
    tokensFlow->maxSize = 0;
    tokensFlow->pointer = 0;
}

void tf_print(struct TokensFlow tokensFlow) {
    for (int i = 0; i < tokensFlow.size; ++i) {
        for (int j = 0; j < tokensFlow.tokens[i].length; ++j) {
            printf("%c", tokensFlow.tokens[i].symbols[j]);
        }
        printf("\n");

    }

}

void tf_printWithType(struct TokensFlow tokensFlow) {
    for (int i = 0; i < tokensFlow.size; ++i) {
        for (int j = 0; j < tokensFlow.tokens[i].length; ++j) {
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
        if (tokensFlowOne.tokens[i].line != tokensFlowTwo.tokens[i].line)
            return 0;

        for (int j = 0; j < tokensFlowOne.tokens[i].length; ++j)
            if (tokensFlowOne.tokens[i].symbols[j] != tokensFlowTwo.tokens[i].symbols[j])
                return 0;

    }
    return 1;
}
//__________________________________________________________________________________________________