#include "B_TerminalSymbols.h"

//__________________________________________________________________________________________________


struct TerminalSymbol ts_newTerminalSymbol(char name[], int size, int type) {
    struct TerminalSymbol terminalSymbol;
    terminalSymbol.name = name;
    terminalSymbol.size = size;
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
    terminalSymbols->OF = ts_newTerminalSymbol("DO", 2, 25);
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
    terminalSymbols->ARRAY = ts_newTerminalSymbol("ARRAY", 5, 54);
    terminalSymbols->RECORD = ts_newTerminalSymbol("RECORD", 6, 55);
    terminalSymbols->CONSTT = ts_newTerminalSymbol("CONST", 5, 57);
    terminalSymbols->INTEGER = ts_newTerminalSymbol("INTEGER", 7, 58);
    terminalSymbols->BOOLEAN = ts_newTerminalSymbol("BOOLEAN", 7, 58);
    terminalSymbols->VAR = ts_newTerminalSymbol("VAR", 3, 59);
    terminalSymbols->PROCEDURE = ts_newTerminalSymbol("PROCEDURE", 9, 60);
    terminalSymbols->BEGIN = ts_newTerminalSymbol("BEGIN", 5, 61);
    terminalSymbols->MODULE = ts_newTerminalSymbol("MODULE", 6, 63);
    terminalSymbols->EOFF = ts_newTerminalSymbol("EOF", 3, 64);

}

int tss_defineType(struct TerminalSymbols terminalSymbols, struct Token token) {
    if (token_equalsWithString(token, terminalSymbols.NULLL.name))
        return terminalSymbols.NULLL.type;
    if (token_equalsWithString(token, terminalSymbols.TIMES.name))
        return terminalSymbols.TIMES.type;
    if (token_equalsWithString(token, terminalSymbols.DIV.name))
        return terminalSymbols.DIV.type;
    if (token_equalsWithString(token, terminalSymbols.MOD.name))
        return terminalSymbols.MOD.type;
    if (token_equalsWithString(token, terminalSymbols.AND.name))
        return terminalSymbols.AND.type;
    if (token_equalsWithString(token, terminalSymbols.PLUS.name))
        return terminalSymbols.PLUS.type;
    if (token_equalsWithString(token, terminalSymbols.MINUS.name))
        return terminalSymbols.MINUS.type;
    if (token_equalsWithString(token, terminalSymbols.OR.name))
        return terminalSymbols.OR.type;
    if (token_equalsWithString(token, terminalSymbols.EQL.name))
        return terminalSymbols.EQL.type;
    if (token_equalsWithString(token, terminalSymbols.NEQ.name))
        return terminalSymbols.NEQ.type;
    if (token_equalsWithString(token, terminalSymbols.LSS.name))
        return terminalSymbols.LSS.type;
    if (token_equalsWithString(token, terminalSymbols.GEQ.name))
        return terminalSymbols.GEQ.type;
    if (token_equalsWithString(token, terminalSymbols.LEQ.name))
        return terminalSymbols.LEQ.type;
    if (token_equalsWithString(token, terminalSymbols.GTR.name))
        return terminalSymbols.GTR.type;
    if (token_equalsWithString(token, terminalSymbols.PERIOD.name))
        return terminalSymbols.PERIOD.type;
    if (token_equalsWithString(token, terminalSymbols.COMMA.name))
        return terminalSymbols.COMMA.type;
    if (token_equalsWithString(token, terminalSymbols.COLON.name))
        return terminalSymbols.COLON.type;
    if (token_equalsWithString(token, terminalSymbols.RPAREN.name))
        return terminalSymbols.RPAREN.type;
    if (token_equalsWithString(token, terminalSymbols.RBRAK.name))
        return terminalSymbols.RBRAK.type;
    if (token_equalsWithString(token, terminalSymbols.OF.name))
        return terminalSymbols.OF.type;
    if (token_equalsWithString(token, terminalSymbols.THEN.name))
        return terminalSymbols.THEN.type;
    if (token_equalsWithString(token, terminalSymbols.DO.name))
        return terminalSymbols.DO.type;
    if (token_equalsWithString(token, terminalSymbols.LPAREN.name))
        return terminalSymbols.LPAREN.type;
    if (token_equalsWithString(token, terminalSymbols.LBRAK.name))
        return terminalSymbols.LBRAK.type;
    if (token_equalsWithString(token, terminalSymbols.NOT.name))
        return terminalSymbols.NOT.type;
    if (token_equalsWithString(token, terminalSymbols.BECOMES.name))
        return terminalSymbols.BECOMES.type;
    if (token_equalsWithString(token, terminalSymbols.NUMBER.name))
        return terminalSymbols.NUMBER.type;
    if (token_equalsWithString(token, terminalSymbols.IDENT.name))
        return terminalSymbols.IDENT.type;
    if (token_equalsWithString(token, terminalSymbols.SEMICOLON.name))
        return terminalSymbols.SEMICOLON.type;
    if (token_equalsWithString(token, terminalSymbols.END.name))
        return terminalSymbols.END.type;
    if (token_equalsWithString(token, terminalSymbols.ELSE.name))
        return terminalSymbols.ELSE.type;
    if (token_equalsWithString(token, terminalSymbols.ELSEIF.name))
        return terminalSymbols.ELSEIF.type;
    if (token_equalsWithString(token, terminalSymbols.IF.name))
        return terminalSymbols.IF.type;
    if (token_equalsWithString(token, terminalSymbols.WHILE.name))
        return terminalSymbols.WHILE.type;
    if (token_equalsWithString(token, terminalSymbols.ARRAY.name))
        return terminalSymbols.ARRAY.type;
    if (token_equalsWithString(token, terminalSymbols.RECORD.name))
        return terminalSymbols.RECORD.type;
    if (token_equalsWithString(token, terminalSymbols.CONSTT.name))
        return terminalSymbols.CONSTT.type;
    if (token_equalsWithString(token, terminalSymbols.INTEGER.name))
        return terminalSymbols.INTEGER.type;
    if (token_equalsWithString(token, terminalSymbols.BOOLEAN.name))
        return terminalSymbols.BOOLEAN.type;
    if (token_equalsWithString(token, terminalSymbols.VAR.name))
        return terminalSymbols.VAR.type;
    if (token_equalsWithString(token, terminalSymbols.PROCEDURE.name))
        return terminalSymbols.PROCEDURE.type;
    if (token_equalsWithString(token, terminalSymbols.BEGIN.name))
        return terminalSymbols.BEGIN.type;
    if (token_equalsWithString(token, terminalSymbols.MODULE.name))
        return terminalSymbols.MODULE.type;
    if (token_equalsWithString(token, terminalSymbols.EOFF.name))
        return terminalSymbols.EOFF.type;

    int sum = 0;
    for (int k = 0; k < token.size; ++k) {
        if (charIsDigit(token.symbols[k]))
            sum++;
    }
    if (sum == token.size)
        return terminalSymbols.NUMBER.type;


    return terminalSymbols.VAR.type;

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
