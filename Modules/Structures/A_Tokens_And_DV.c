#include <stdio.h>
#include <stdlib.h>
#include "A_Tokens_And_DV.h"

//__________________________________________________________________________________________________
const int TOKEN_INIT_MAXSIZE = 8;

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
    //TODO so interesting
    if (token->maxSize == 0 || token->size < 0)
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

int token_equalsWithString(struct Token token, const char *name) {
    for (int i = 0; i < token.size; ++i)
        if (token.symbols[i] != name[i])
            return 0;
    return 1;
}

void token_print(struct Token token) {
    for (int i = 0; i < token.size; ++i)
        printf("%c", token.symbols[i]);
}

int token_defineType(struct Token token, struct TerminalSymbols terminalSymbols) {
    if (token_equalsWithString(token, terminalSymbols.NULLL.name))
        return terminalSymbols.NULLL.type;
    if (token_equalsWithString(token, terminalSymbols.TIMES.name))
        return terminalSymbols.TIMES.type;
    if (token_equalsWithString(token, terminalSymbols.DIV.name))
        return terminalSymbols.DIV.type;
    if (token_equalsWithString(token, terminalSymbols.MOD.name))
        return terminalSymbols.MOD.type;
    if (token_equalsWithString(token, terminalSymbols.AND.name))
        return terminalSymbols.AND.type;
    if (token_equalsWithString(token, terminalSymbols.PLUS.name))
        return terminalSymbols.PLUS.type;
    if (token_equalsWithString(token, terminalSymbols.MINUS.name))
        return terminalSymbols.MINUS.type;
    if (token_equalsWithString(token, terminalSymbols.OR.name))
        return terminalSymbols.OR.type;
    if (token_equalsWithString(token, terminalSymbols.EQL.name))
        return terminalSymbols.EQL.type;
    if (token_equalsWithString(token, terminalSymbols.NEQ.name))
        return terminalSymbols.NEQ.type;
    if (token_equalsWithString(token, terminalSymbols.LSS.name))
        return terminalSymbols.LSS.type;
    if (token_equalsWithString(token, terminalSymbols.GEQ.name))
        return terminalSymbols.GEQ.type;
    if (token_equalsWithString(token, terminalSymbols.LEQ.name))
        return terminalSymbols.LEQ.type;
    if (token_equalsWithString(token, terminalSymbols.GTR.name))
        return terminalSymbols.GTR.type;
    if (token_equalsWithString(token, terminalSymbols.PERIOD.name))
        return terminalSymbols.PERIOD.type;
    if (token_equalsWithString(token, terminalSymbols.COMMA.name))
        return terminalSymbols.COMMA.type;
    if (token_equalsWithString(token, terminalSymbols.COLON.name))
        return terminalSymbols.COLON.type;
    if (token_equalsWithString(token, terminalSymbols.RPAREN.name))
        return terminalSymbols.RPAREN.type;
    if (token_equalsWithString(token, terminalSymbols.RBRAK.name))
        return terminalSymbols.RBRAK.type;
    if (token_equalsWithString(token, terminalSymbols.OF.name))
        return terminalSymbols.OF.type;
    if (token_equalsWithString(token, terminalSymbols.THEN.name))
        return terminalSymbols.THEN.type;
    if (token_equalsWithString(token, terminalSymbols.DO.name))
        return terminalSymbols.DO.type;
    if (token_equalsWithString(token, terminalSymbols.LPAREN.name))
        return terminalSymbols.LPAREN.type;
    if (token_equalsWithString(token, terminalSymbols.LBRAK.name))
        return terminalSymbols.LBRAK.type;
    if (token_equalsWithString(token, terminalSymbols.NOT.name))
        return terminalSymbols.NOT.type;
    if (token_equalsWithString(token, terminalSymbols.BECOMES.name))
        return terminalSymbols.BECOMES.type;
    if (token_equalsWithString(token, terminalSymbols.NUMBER.name))
        return terminalSymbols.NUMBER.type;
    if (token_equalsWithString(token, terminalSymbols.IDENT.name))
        return terminalSymbols.IDENT.type;
    if (token_equalsWithString(token, terminalSymbols.SEMICOLON.name))
        return terminalSymbols.SEMICOLON.type;
    if (token_equalsWithString(token, terminalSymbols.END.name))
        return terminalSymbols.END.type;
    if (token_equalsWithString(token, terminalSymbols.ELSE.name))
        return terminalSymbols.ELSE.type;
    if (token_equalsWithString(token, terminalSymbols.ELSEIF.name))
        return terminalSymbols.ELSEIF.type;
    if (token_equalsWithString(token, terminalSymbols.IF.name))
        return terminalSymbols.IF.type;
    if (token_equalsWithString(token, terminalSymbols.WHILE.name))
        return terminalSymbols.WHILE.type;
    if (token_equalsWithString(token, terminalSymbols.ARRAY.name))
        return terminalSymbols.ARRAY.type;
    if (token_equalsWithString(token, terminalSymbols.RECORD.name))
        return terminalSymbols.RECORD.type;
    if (token_equalsWithString(token, terminalSymbols.CONSTT.name))
        return terminalSymbols.CONSTT.type;
    if (token_equalsWithString(token, terminalSymbols.INTEGER.name))
        return terminalSymbols.INTEGER.type;
    if (token_equalsWithString(token, terminalSymbols.BOOLEAN.name))
        return terminalSymbols.BOOLEAN.type;
    if (token_equalsWithString(token, terminalSymbols.VAR.name))
        return terminalSymbols.VAR.type;
    if (token_equalsWithString(token, terminalSymbols.PROCEDURE.name))
        return terminalSymbols.PROCEDURE.type;
    if (token_equalsWithString(token, terminalSymbols.BEGIN.name))
        return terminalSymbols.BEGIN.type;
    if (token_equalsWithString(token, terminalSymbols.MODULE.name))
        return terminalSymbols.MODULE.type;
    if (token_equalsWithString(token, terminalSymbols.EOFF.name))
        return terminalSymbols.EOFF.type;

    int sum = 0;
    for (int k = 0; k < token.size; ++k)
        if (charIsDigit(token.symbols[k]))
            sum++;
        else break;

    if (sum == token.size)
        return terminalSymbols.NUMBER.type;


    return terminalSymbols.IDENT.type;

}

//__________________________________________________________________________________________________
const int V_MAX_NAMELENGTH = 20;


void v_setName(struct Variable *variable, char name[], int nameLength) {
    if (variable->nameLength > V_MAX_NAMELENGTH) {
        printf("MAXLENGTH = %d, length of var%s = %d", V_MAX_NAMELENGTH, name, nameLength);
        return;
    }
    for (int i = 0; i < nameLength; ++i)
        variable->name[i] = name[i];
    variable->nameLength = nameLength;

}

//TODO just awful signature, think where we can store global variable terminalSymbols?
void v_createFromToken(struct Variable *variable, struct Token *token, struct TerminalSymbols terminalSymbols) {
    v_setName(variable, token->symbols, token->size);
    variable->type = INTEG;

    //if (token->type == terminalSymbols.BOOLEAN.type)
    //    variable->type = BOOLE;
    //if (token->type == terminalSymbols.INTEGER.type)
    //    variable->type = INTEG;

}

int v_equals(struct Variable variableOne, struct Variable variableTwo) {
    if (variableOne.nameLength != variableTwo.nameLength)
        return 0;
    if (variableOne.type != variableTwo.type)
        return 0;
    for (int i = 0; i < variableOne.nameLength; ++i)
        if (variableOne.name[i] != variableTwo.name[i])
            return 0;
    return 1;


}

//__________________________________________________________________________________________________

const int DV_INIT_MAXSIZE = 20;

void dv_allocatedMemory(struct DeclaredVariables *declaredVariables) {
    declaredVariables->maxSize = declaredVariables->maxSize * 2;
    declaredVariables->variables = realloc(declaredVariables->variables,
                                           sizeof(struct Variable) * declaredVariables->maxSize);
}

void dv_initialize(struct DeclaredVariables *declaredVariables) {
    declaredVariables->size = 0;
    declaredVariables->maxSize = DV_INIT_MAXSIZE;
    declaredVariables->variables = malloc(sizeof(struct Variable) * DV_INIT_MAXSIZE);
}

//TODO just awful signature, think where we can store global variable terminalSymbols?
void dv_addVarialbe(struct DeclaredVariables *declaredVariables, struct Token *token,
                    struct TerminalSymbols terminalSymbols) {
    if (declaredVariables->maxSize == 0)
        dv_initialize(declaredVariables);
    if (declaredVariables->size == declaredVariables->maxSize - 1)
        dv_allocatedMemory(declaredVariables);
    struct Variable variable;
    v_createFromToken(&variable, token, terminalSymbols);
    if (dv_containsVariable(*declaredVariables, variable) == 0) {
        declaredVariables->variables[declaredVariables->size] = variable;
        declaredVariables->size++;
    }

}

int dv_equals(struct DeclaredVariables declaredVariablesOne, struct DeclaredVariables declaredVariablesTwo) {
    if (declaredVariablesOne.size != declaredVariablesTwo.size)
        return 0;
    for (int i = 0; i < declaredVariablesTwo.size; ++i) {
        if (declaredVariablesOne.variables[i].type != declaredVariablesTwo.variables[i].type)
            return 0;
        for (int j = 0; j < declaredVariablesOne.variables[i].nameLength; j++)
            if (declaredVariablesOne.variables[i].name[j] != declaredVariablesTwo.variables[i].name[j])
                return 0;

    }
    return 1;
}


int dv_containsVariable(struct DeclaredVariables declaredVariables, struct Variable variable) {
    for (int i = 0; i < declaredVariables.size; ++i)
        if (v_equals(variable, declaredVariables.variables[i]) == 1)
            return 1;

    return 0;

}

void dv_printWithType(struct DeclaredVariables declaredVariables) {
    for (int i = 0; i < declaredVariables.size; ++i) {
        for (int j = 0; j < declaredVariables.variables[i].nameLength; ++j) {
            printf("%c", declaredVariables.variables[i].name[j]);
        }
        printf("\t%d\n", declaredVariables.variables[i].type);
    }
}

//__________________________________________________________________________________________________
const int TF_INIT_MAXSIZE = 16;

void tf_initialize(struct TokensFlow *tokensFlow) {
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
    tokensFlow->tokens[tokensFlow->size] = *token;
    tokensFlow->size++;
}

struct Token tf_next(struct TokensFlow *tokensFlow) {
    tokensFlow->currentToken = tokensFlow->tokens[tokensFlow->pointer];
    tokensFlow->pointer++;
    return tokensFlow->currentToken;
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

        for (int j = 0; j < tokensFlowOne.tokens[i].size; ++j)
            if (tokensFlowOne.tokens[i].symbols[j] != tokensFlowTwo.tokens[i].symbols[j])
                return 0;

    }
    return 1;
}
//__________________________________________________________________________________________________