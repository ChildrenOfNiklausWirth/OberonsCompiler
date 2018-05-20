#include <stdio.h>
#include "Z_Tokens.c"
#include "Y_TerminalSymbols.c"
#include "X_DeclaredVariables.c"

struct TerminalSymbols terminalSymbols;

struct Token readNextToken(FILE *file, char c) {
    int index = 0;
    struct Token token;
    token.length = 0;
    while (c != ' ' && c != ';' && c != '\n' && c != EOF) {
        if (tss_containsChar(terminalSymbols, c) == 0) {
            token.symbols[index] = c;
            token.length++;
            index++;
            fscanf(file, "%c", &c);
        } else
            break;
    }
    if (tss_containsToken(terminalSymbols, token) == 1)
        token.type = 't';
    else
        token.type = 'n';

    return token;

}

//TODO  находить терминальные символы без пробелов, при этом не теряя их
void tokensParsing(char *fileName, struct TokensFlow *tokensFlow, struct DeclaredVariables *declaredVariables) {
    tss_initialize(&terminalSymbols);

    FILE *file = fopen(fileName, "r");
    char c;
    while (fscanf(file, "%c", &c) != EOF) {
        struct Token token = readNextToken(file, c);
        if (token.length != 0)//TODO костыль
            tf_addToken(tokensFlow, &token);
        if (tss_containsChar(terminalSymbols, c) == 1) {//TODO костыль
            token = newToken(c, 1);
            tf_addToken(tokensFlow, &token);
        }

    }


}

