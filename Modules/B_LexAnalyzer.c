#include "B_LexAnalyzer.h"


enum OC {
    WINDOWS, LINUX
};
enum OC oc = LINUX;//TODO check before using

int numberOfLine;
struct TokensFlow lexTokensFlow;

void parseCommentaries(FILE *file, char *c) {
    do {
        fscanf(file, "%c", c);
    } while (*c != '*');
    fscanf(file, "%c", c);
    if (*c != '/')
        parseCommentaries(file, c);
    else
        fscanf(file, "%c", c);
}

int readNextToken(FILE *file, Token *token) {
    int tokenLength = 0;
    char firstSymbol, lastSymbol;

    token->line = numberOfLine;

    if (fscanf(file, "%c", &firstSymbol) == EOF)
        return 0;

    //Missing of  spaces and \n
    while (firstSymbol == ' ' || firstSymbol == '\n') {
        if (firstSymbol == '\n')
            numberOfLine++;
        if (fscanf(file, "%c", &firstSymbol) == EOF)
            return 0;

    }

    //Parsing of comments
    if (firstSymbol == '/') {
        fscanf(file, "%c", &firstSymbol);
        if (firstSymbol == '*') {
            parseCommentaries(file, &firstSymbol);
            return readNextToken(file, token);
        } else
            switch (firstSymbol) {
                case '\n':
                    switch (oc) {
                        case WINDOWS:
                            fseek(file, -2, SEEK_CUR);
                            break;
                        case LINUX:
                            fseek(file, -1, SEEK_CUR);
                            break;
                    }
                    break;
                default:
                    fseek(file, -1, SEEK_CUR);
            }

    }

    if (fscanf(file, "%c", &lastSymbol) == EOF) {
        token_initialize(token, 1);
        token->length = 1;
        token->symbols[0] = firstSymbol;
        token->type = token_defineType(*token, terminalSymbols);

        return 1;

    } else if (bothCharIsMathSymbol(firstSymbol, lastSymbol)) {

        tokenLength = 2;
        fseek(file, 1, SEEK_CUR);


    } else if (bothCharIsDigit(firstSymbol, lastSymbol)) {

        tokenLength = 1;
        while (charIsDigit(lastSymbol)) {
            fscanf(file, "%c", &lastSymbol);
            tokenLength++;
        }

    } else if (charIsASeparatingTerminalSymbol(terminalSymbols, firstSymbol)) {

        tokenLength = 1;

    } else {

        tokenLength = 1;
        while (lastSymbol != '\n' && lastSymbol != ' ' &&
               !charIsASeparatingTerminalSymbol(terminalSymbols, lastSymbol)) {
            tokenLength++;
            fscanf(file, "%c", &lastSymbol);
        }

    }

    token_initialize(token, tokenLength);

    if (oc == WINDOWS)
        if (lastSymbol == '\n')
            fseek(file, -1, SEEK_CUR);


    fseek(file, -tokenLength - 1, SEEK_CUR);


    for (int i = 0; i < tokenLength; ++i)
        token->symbols[i] = (char) getc(file);


    token->type = token_defineType(*token, terminalSymbols);


    return 1;


}

void lexAnalysis(char *fileName) {
    numberOfLine = 1;

    tf_initialize(&lexTokensFlow);
    tss_initialize(&terminalSymbols);
    FILE *file = fopen(fileName, "r");

    Token token;
    int result = 1;
    while (result == 1) {
        result = readNextToken(file, &token);
        if (result != 0)
            tf_addToken(&lexTokensFlow, &token);
    }


    if (lexTokensFlow.size == 0)
        printf("Probably wrong path");

}

void Mark(char msg[]) {
    printf("Error in line number%d\n", lexTokensFlow.current->line);
    printf("%s\n\n", msg);
}
