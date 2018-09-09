#include <malloc.h>
#include "B_LexAnalyzer.h"


enum OS {
    WINDOWS, LINUX, UNSUPPORTED
};

enum OS os = OS_TYPE;

int numberOfLine;
struct TokensFlow lexTokensFlow;
FILE *lexOutputFile;

int parseCommentaries(FILE *file, char *c) {
    do {
        if (fscanf(file, "%c", c) == EOF)
            return 0;
        if (*c == '\n')
            numberOfLine++;
    } while (*c != '*');
    fscanf(file, "%c", c);
    if (*c != '/')
        parseCommentaries(file, c);
    else {
        fscanf(file, "%c", c);
        return 1;
    }
}

int readNextToken(FILE *file, Token *token) {
    int tokenLength = 0;
    char firstSymbol, lastSymbol;


    if (fscanf(file, "%c", &firstSymbol) == EOF)
        return 0;

    //Missing of  spaces and \n
    while (firstSymbol == ' ' || firstSymbol == '\n') {
        if (firstSymbol == '\n')
            numberOfLine++;
        if (fscanf(file, "%c", &firstSymbol) == EOF)
            return 0;
    }

    int parsResult;
    //Parsing of comments
    if (firstSymbol == '/') {
        fscanf(file, "%c", &firstSymbol);
        if (firstSymbol == '*') {
            parsResult = parseCommentaries(file, &firstSymbol);
            if (!parsResult)
                Mark("Incorrect comment", numberOfLine);
            if (firstSymbol == '\n')
                numberOfLine++;
            return readNextToken(file, token);
        } else
            switch (firstSymbol) {
                case '\n':
                    switch (os) {
                        case WINDOWS:
                            fseek(file, -2, SEEK_CUR);
                            break;
                        case LINUX:
                            fseek(file, -1, SEEK_CUR);
                            break;
                        case UNSUPPORTED:
                            fseek(file, -1, SEEK_CUR);
                            break;
                    }
                    break;
                default:
                    fseek(file, -1, SEEK_CUR);
            }

    }

    if (fscanf(file, "%c", &lastSymbol) == EOF) {
        token_initialize(token, 2);
        token->length = 2;
        token->symbols[0] = firstSymbol;
        token->symbols[1] = '\0';
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

    token_initialize(token, tokenLength + 1);

    if (os == WINDOWS)
        if (lastSymbol == '\n')
            fseek(file, -1, SEEK_CUR);


    fseek(file, -tokenLength - 1, SEEK_CUR);


    for (int i = 0; i < tokenLength; ++i) {
        token->symbols[i] = (char) getc(file);
    }

    token->symbols[tokenLength] = '\0';

    token->type = token_defineType(*token, terminalSymbols);


    return 1;


}

void lexAnalysis(FILE *inputFile, FILE *outputFile) {
    lexOutputFile = outputFile;
    numberOfLine = 1;

    if (os == UNSUPPORTED) {
        printf("Unsupported OS type. Working in Linux compatibility mode.");
    }

    tf_initialize(&lexTokensFlow);
    tss_initialize(&terminalSymbols);

    Token token;
    int result = 1;
    while (result == 1) {
        result = readNextToken(inputFile, &token);
        token.line = numberOfLine;
        if (result != 0)
            tf_addToken(&lexTokensFlow, &token);
    }
}

void Mark(char msg[], int line) {

    if (line < 0) {
        line = lexTokensFlow.current->line;
    }

    if (lexOutputFile != NULL)
        fprintf(lexOutputFile, "Line number: %d. Error: \"%s\". \n", line, msg);
    else
        printf("\nLine number: %d. Error: \"%s\". \n", line, msg);
}
