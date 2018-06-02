#include <stdio.h>
#include "Z_Tokens.c"
#include "Y_TerminalSymbols.c"
#include "X_DeclaredVariables.c"

struct TerminalSymbols terminalSymbols;

struct Token readNextToken(FILE *file, char currentSymbol) {
    while (currentSymbol == ' ' || currentSymbol == '\n')
        currentSymbol = (char) getc(file);
    struct Token token;
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

    int type = tss_defineType(terminalSymbols, token);
    token.type = type;

    return token;


}

//TODO заполнение DeclaredVariables
void tokensParsing(char *fileName, struct TokensFlow *tokensFlow, struct DeclaredVariables *declaredVariables) {
    tss_initialize(&terminalSymbols);

    FILE *file = fopen(fileName, "r");
    char c;
    while (fscanf(file, "%c", &c) != EOF) {

        struct Token token = readNextToken(file, c);
        tf_addToken(tokensFlow, &token);

    }

}