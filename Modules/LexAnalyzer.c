
#include "LexAnalyzer.h"


enum OS {
    WINDOWS, LINUX, UNSUPPORTED
};

enum OS os = OS_TYPE;

int numberOfLine;
struct TokensFlow lexTokensFlow;
FILE *lexOutputFile;


int charIsDigit(char c) {
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' ||
        c == '0')
        return 1;
    return 0;
}

int bothCharIsDigit(char c1, char c2) {
    if ((c1 == '0' || c1 == '1' || c1 == '2' ||
         c1 == '3' || c1 == '4' || c1 == '5' ||
         c1 == '6' || c1 == '7' || c1 == '8' || c1 == '9')
        &
        (c2 == '0' ||
         c2 == '1' ||
         c2 == '2' ||
         c2 == '3' ||
         c2 == '4' ||
         c2 == '5' ||
         c2 == '6' ||
         c2 == '7' ||
         c2 == '8' ||
         c2 == '9'))
        return 1;
    return 0;

}

int bothCharIsMathSymbol(char c1, char c2) {
    if ((c1 == '=' || c1 == '<' || c1 == '>' || c1 == ':') & (c2 == '=' || c2 == '<' || c2 == '>' || c2 == ':'))
        return 1;
    return 0;
}

int charIsASeparatingTerminalSymbol(struct TerminalSymbols terminalSymbols, char symbol) {

    if (symbol == terminalSymbols.TIMES.name[0])
        return 1;
    if (symbol == terminalSymbols.PLUS.name[0])
        return 1;
    if (symbol == terminalSymbols.MINUS.name[0])
        return 1;
    if (symbol == terminalSymbols.EQL.name[0])
        return 1;
    if (symbol == terminalSymbols.NEQ.name[0])
        return 1;
    if (symbol == terminalSymbols.LSS.name[0])
        return 1;
    if (symbol == terminalSymbols.GTR.name[0])
        return 1;
    if (symbol == terminalSymbols.PERIOD.name[0])
        return 1;
    if (symbol == terminalSymbols.COMMA.name[0])
        return 1;
    if (symbol == terminalSymbols.COLON.name[0])
        return 1;
    if (symbol == terminalSymbols.RPAREN.name[0])
        return 1;
    if (symbol == terminalSymbols.LPAREN.name[0])
        return 1;
    if (symbol == terminalSymbols.RBRAK.name[0])
        return 1;
    if (symbol == terminalSymbols.LBRAK.name[0])
        return 1;
    if (symbol == terminalSymbols.NOT.name[0])
        return 1;
    if (symbol == terminalSymbols.SEMICOLON.name[0])
        return 1;
    return 0;
}


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
    return 0;
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
    syntaxError = 0;

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

    syntaxError = 1;

    if (line < 0) {
        line = lexTokensFlow.current->line;
    }

    if (lexOutputFile != NULL)
        fprintf(lexOutputFile, "Line number: %d. Error: \"%s\". \n", line, msg);
    else
        printf("\nLine number: %d. Error: \"%s\". \n", line, msg);
}
