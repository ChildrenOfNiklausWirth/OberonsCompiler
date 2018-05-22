#include <stdio.h>

//__________________________________________________________________________________________________

struct Token {
    //int numberOfLine;//Для информации об ошибках
    int type;//Тип токена {n,t}
    char symbols[30];
    int length;
};

struct Token newToken(const char symbols[], int length) {
    struct Token token;
    for (int i = 0; i < length; ++i)
        token.symbols[i] = symbols[i];
    token.length = length;
    return token;


}

struct Token newTokenWithType(const char *symbols, int length, int type) {
    struct Token token;
    for (int i = 0; i < length; ++i)
        token.symbols[i] = symbols[i];
    token.length = length;
    token.type = type;
    return token;
}

//__________________________________________________________________________________________________


struct TokensFlow {
    struct Token tokens[50];
    int maxSize;
    int size;

};


void tf_initialize(struct TokensFlow *tokensFlow) {
    tokensFlow->maxSize = 50;
    tokensFlow->size = 0;
}


void tf_addToken(struct TokensFlow *tokensFlow, struct Token *token) {
    tokensFlow->tokens[tokensFlow->size] = *token;
    tokensFlow->size++;
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

void tf_printWithTypeTwoTokensFlow(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo) {
    for (int i = 0; i < tokensFlowOne.size; ++i) {
        for (int j = 0; j < tokensFlowOne.tokens[i].length; ++j) {
            printf("%c", tokensFlowOne.tokens[i].symbols[j]);
        }
        printf("\t\t\ttype : %d\t\t", tokensFlowOne.tokens[i].type);

        for (int j = 0; j < tokensFlowTwo.tokens[i].length; ++j) {
            printf("%c", tokensFlowTwo.tokens[i].symbols[j]);
        }
        printf("\t\t\t\ttype : %d\n", tokensFlowTwo.tokens[i].type);

    }
}

int tf_equals(struct TokensFlow tokensFlowOne, struct TokensFlow tokensFlowTwo) {
    if (tokensFlowOne.size != tokensFlowTwo.size)
        return 0;
    for (int i = 0; i < tokensFlowOne.size; ++i) {
        if (tokensFlowOne.tokens[i].length != tokensFlowTwo.tokens[i].length ||
            tokensFlowOne.tokens[i].type != tokensFlowTwo.tokens[i].type)
            return 0;
        for (int j = 0; j < tokensFlowOne.tokens[i].length; ++j) {
            if (tokensFlowOne.tokens[i].symbols[j] != tokensFlowTwo.tokens[i].symbols[j])
                return 0;
        }
    }
    return 1;
}
//__________________________________________________________________________________________________