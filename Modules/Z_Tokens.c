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

//__________________________________________________________________________________________________