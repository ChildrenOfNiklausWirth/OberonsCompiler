#include "B_TerminalSymbols.h"

//__________________________________________________________________________________________________


struct TerminalSymbol ts_newTerminalSymbol(char name[], int nameLength, int type) {
    struct TerminalSymbol terminalSymbol;
    terminalSymbol.name = name;
    terminalSymbol.nameLength = nameLength;
    terminalSymbol.type = type;
    return terminalSymbol;
}

//__________________________________________________________________________________________________
void tss_initialize(struct TerminalSymbols *terminalSymbols) {
    terminalSymbols->NULLL = ts_newTerminalSymbol("NULL", 4, 0);
    terminalSymbols->TIMES = ts_newTerminalSymbol("*", 1, 1);
    terminalSymbols->DIV = ts_newTerminalSymbol("/", 1, 3);
    terminalSymbols->MOD = ts_newTerminalSymbol("MOD", 3, 4);
    terminalSymbols->AND = ts_newTerminalSymbol("AND", 3, 5);
    terminalSymbols->PLUS = ts_newTerminalSymbol("+", 1, 6);
    terminalSymbols->MINUS = ts_newTerminalSymbol("-", 1, 7);
    terminalSymbols->OR = ts_newTerminalSymbol("&", 1, 8);
    terminalSymbols->EQL = ts_newTerminalSymbol("=", 1, 9);
    terminalSymbols->NEQ = ts_newTerminalSymbol("#", 1, 10);
    terminalSymbols->LSS = ts_newTerminalSymbol("<", 1, 11);
    terminalSymbols->GEQ = ts_newTerminalSymbol(">=", 2, 12);
    terminalSymbols->LEQ = ts_newTerminalSymbol("<=", 2, 13);
    terminalSymbols->GTR = ts_newTerminalSymbol(">", 1, 14);
    terminalSymbols->PERIOD = ts_newTerminalSymbol(".", 1, 18);
    terminalSymbols->COMMA = ts_newTerminalSymbol(",", 1, 19);
    terminalSymbols->COLON = ts_newTerminalSymbol(":", 1, 20);
    terminalSymbols->RPAREN = ts_newTerminalSymbol(")", 1, 22);
    terminalSymbols->RBRAK = ts_newTerminalSymbol("]", 1, 23);
    terminalSymbols->OF = ts_newTerminalSymbol("OF", 2, 25);
    terminalSymbols->THEN = ts_newTerminalSymbol("THEN", 4, 26);
    terminalSymbols->DO = ts_newTerminalSymbol("DO", 2, 27);
    terminalSymbols->LPAREN = ts_newTerminalSymbol("(", 1, 29);
    terminalSymbols->LBRAK = ts_newTerminalSymbol("[", 1, 30);
    terminalSymbols->NOT = ts_newTerminalSymbol("`", 1, 32);
    terminalSymbols->BECOMES = ts_newTerminalSymbol(":=", 2, 33);
    terminalSymbols->NUMBER = ts_newTerminalSymbol("number", 6, 34);
    terminalSymbols->IDENT = ts_newTerminalSymbol("ident", 5, 37);
    terminalSymbols->SEMICOLON = ts_newTerminalSymbol(";", 1, 38);
    terminalSymbols->END = ts_newTerminalSymbol("END", 3, 40);
    terminalSymbols->ELSE = ts_newTerminalSymbol("ELSE", 4, 41);
    terminalSymbols->ELSEIF = ts_newTerminalSymbol("ELSEIF", 6, 42);
    terminalSymbols->IF = ts_newTerminalSymbol("IF", 2, 44);
    terminalSymbols->WHILE = ts_newTerminalSymbol("WHILE", 5, 46);
    terminalSymbols->ARR = ts_newTerminalSymbol("ARRAY", 5, 54);
    terminalSymbols->REC = ts_newTerminalSymbol("RECORD", 6, 55);
    terminalSymbols->CONSTT = ts_newTerminalSymbol("CONST", 5, 57);
    terminalSymbols->INT = ts_newTerminalSymbol("INTEGER", 7, 37);
    terminalSymbols->BOOL = ts_newTerminalSymbol("BOOLEAN", 7, 37);
    terminalSymbols->VAR = ts_newTerminalSymbol("VAR", 3, 59);
    terminalSymbols->PROCEDURE = ts_newTerminalSymbol("PROCEDURE", 9, 60);
    terminalSymbols->BEGIN = ts_newTerminalSymbol("BEGIN", 5, 61);
    terminalSymbols->MODULE = ts_newTerminalSymbol("MODULE", 6, 63);
    terminalSymbols->EOFF = ts_newTerminalSymbol("EOF", 3, 64);

}

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
    if (symbol == terminalSymbols.DIV.name[0])
        return 1;
    if (symbol == terminalSymbols.PLUS.name[0])
        return 1;
    if (symbol == terminalSymbols.MINUS.name[0])
        return 1;
    if (symbol == terminalSymbols.OR.name[0])
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


//__________________________________________________________________________________________________
