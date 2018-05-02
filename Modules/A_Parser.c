#include <stdio.h>
#include "Z_Structs.c"


void readNextToken(FILE *file, int currentTokenIndex, char c, struct Token *tokens) {
    int index = 0;
    tokens[currentTokenIndex].length = 0;
    while (c != ' ' && c != '\n' && c != EOF && c != ';') {
        tokens[currentTokenIndex].symbols[index] = c;
        tokens[currentTokenIndex].length++;
        index++;
        fscanf(file, "%c", &c);
    }

}


void leksParser(char *fileName, struct Token *tokens, int *tokensDigit) {
    FILE *file = fopen(fileName, "r");
    char c;
    *tokensDigit = 0;
    while (fscanf(file, "%c", &c) != EOF) {
        readNextToken(file, *tokensDigit, c, tokens);
        if (c != '\n')//TODO йняршкэ
            *tokensDigit = *tokensDigit + 1;
    }

};

