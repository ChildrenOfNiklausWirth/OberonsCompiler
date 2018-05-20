#include <stdlib.h>
#include <stdio.h>


//__________________________________________________________________________________________________


struct Token {
    //int numberOfLine;//Для информации об ошибках
    //char type[10];//Тип токена
    int indexOfNextSymbol;
    char symbols[30];
    int length;
};

//__________________________________________________________________________________________________


struct TokensFlow {
    int size;
    int indexOfNextToken;
    struct Token tokens[50];

};


void tf_initialize(struct TokensFlow *tokensFlow) {
    tokensFlow->size = 0;
    tokensFlow->indexOfNextToken = 0;
}


void tf_addToken(struct TokensFlow *tokensFlow, struct Token *token) {
    tokensFlow->tokens[tokensFlow->indexOfNextToken] = *token;
    tokensFlow->indexOfNextToken++;
    tokensFlow->size++;
}


void printTokensFlow(struct TokensFlow tokensFlow){
    for (int i = 0; i < tokensFlow.size; ++i) {
        for (int j = 0; j < tokensFlow.tokens[i].length; ++j) {
            printf("%c", tokensFlow.tokens[i].symbols[j]);
        }
        printf("\n");

    }

}

//__________________________________________________________________________________________________