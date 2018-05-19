#include <stdio.h>
#include "Z_Tokens.c"


struct Token readNextToken(FILE *file, char c) {
    int index = 0;
    struct Token token;
    token.length = 0;
    while (c != ' ' && c != '\n' && c != EOF && c != ';') {
        token.symbols[index] = c;
        token.length++;
        index++;
        fscanf(file, "%c", &c);
    }
    return token;

}

void tokensParsing(char *fileName, struct TokensFlow *tokensFlow) {
    FILE *file = fopen(fileName, "r");
    char c;
    while (fscanf(file, "%c", &c) != EOF) {
        struct Token token = readNextToken(file, c);
        addToken(tokensFlow, &token);
    }


}

