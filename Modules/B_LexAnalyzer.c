#include "B_LexAnalyzer.h"

int numberOfLine = 1;
struct TokensFlow tokensFlow;

Token readNextToken(FILE *file, char currentSymbol) {

    Token token;
    token_initialize(&token);
    token.line = numberOfLine;

    while (currentSymbol == ' ' || currentSymbol == '\n') {
        if (currentSymbol == '\n')
            numberOfLine++;
        currentSymbol = (char) getc(file);
    }

    char nextSymbol = (char) fgetc(file);

    if (bothCharIsMathSymbol(currentSymbol, nextSymbol)) {
        token_addSymbol(&token, currentSymbol);
        token_addSymbol(&token, nextSymbol);
    } else if (bothCharIsDigit(currentSymbol, nextSymbol)) {
        ungetc(nextSymbol, file);
        while (charIsDigit(currentSymbol)) {
            token_addSymbol(&token, currentSymbol);
            if ((fscanf(file, "%c", &currentSymbol)) == EOF)
                break;
        }
        ungetc(currentSymbol, file);
    } else if (charIsASeparatingTerminalSymbol(terminalSymbols, currentSymbol)) {
        token_addSymbol(&token, currentSymbol);
        ungetc(nextSymbol, file);
    } else {
        ungetc(nextSymbol, file);
        while (currentSymbol != ' ' && currentSymbol != '\n' &&
               !charIsASeparatingTerminalSymbol(terminalSymbols, currentSymbol)) {
            token_addSymbol(&token, currentSymbol);
            if ((fscanf(file, "%c", &currentSymbol)) == EOF)
                break;
            if (charIsASeparatingTerminalSymbol(terminalSymbols, currentSymbol)) {
                ungetc(currentSymbol, file);
                break;
            }
        }
    }

    int type = token_defineType(token, terminalSymbols);
    token.type = type;

    return token;


}

void lexAnalysis(char *fileName) {

    tf_initialize(&tokensFlow);
    tss_initialize(&terminalSymbols);
    FILE *file = fopen(fileName, "r");
    char c;

    while (fscanf(file, "%c", &c) != EOF) {
        Token token = readNextToken(file, c);
        tf_addToken(&tokensFlow, &token);
    }


    if (tokensFlow.size == 0)
        printf("Probably wrong path");

}

void Mark(char msg[]) {
    printf("Error in line number%d\n", tokensFlow.current->line);
    printf("%s", msg);
}