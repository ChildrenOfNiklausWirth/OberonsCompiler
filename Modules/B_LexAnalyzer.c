#include "B_LexAnalyzer.h"


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

    int type = token_defineType(token, terminalSymbols);
    token.type = type;

    return token;


}

void lexAnalysis(char *fileName, struct TokensFlow *tokensFlow, struct DeclaredVariables *declaredVariables) {
    tf_initialize(tokensFlow);
    tss_initialize(&terminalSymbols);
    dv_initialize(declaredVariables);
    FILE *file = fopen(fileName, "r");
    char c;
    while (fscanf(file, "%c", &c) != EOF) {

        struct Token token = readNextToken(file, c);
        tf_addToken(tokensFlow, &token);
        if (token.type == terminalSymbols.IDENT.type)
            dv_addVarialbe(declaredVariables, &token, terminalSymbols);

    }


    if (tokensFlow->size == 0)
        printf("Probably wrong path");

}