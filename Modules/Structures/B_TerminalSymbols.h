#ifndef OBERONSCOMPILER_B_TERMINALSYMBOLS_H
#define OBERONSCOMPILER_B_TERMINALSYMBOLS_H

struct TerminalSymbol {
    char *name;
    int size;
    int type;
};

struct TerminalSymbol ts_newTerminalSymbol(char name[], int size, int type);

//__________________________________________________________________________________________________

struct TerminalSymbols {
    struct TerminalSymbol NULLL;
    struct TerminalSymbol TIMES;
    struct TerminalSymbol DIV;
    struct TerminalSymbol MOD;
    struct TerminalSymbol AND;
    struct TerminalSymbol PLUS;
    struct TerminalSymbol MINUS;
    struct TerminalSymbol OR;
    struct TerminalSymbol EQL;
    struct TerminalSymbol NEQ;
    struct TerminalSymbol LSS;
    struct TerminalSymbol GEQ;
    struct TerminalSymbol LEQ;
    struct TerminalSymbol GTR;
    struct TerminalSymbol PERIOD;
    struct TerminalSymbol COMMA;
    struct TerminalSymbol COLON;
    struct TerminalSymbol RPAREN;
    struct TerminalSymbol RBRAK;
    struct TerminalSymbol OF;
    struct TerminalSymbol THEN;
    struct TerminalSymbol DO;
    struct TerminalSymbol LPAREN;
    struct TerminalSymbol LBRAK;
    struct TerminalSymbol NOT;
    struct TerminalSymbol BECOMES;
    struct TerminalSymbol NUMBER;
    struct TerminalSymbol IDENT;
    struct TerminalSymbol SEMICOLON;
    struct TerminalSymbol END;
    struct TerminalSymbol ELSE;
    struct TerminalSymbol ELSEIF;
    struct TerminalSymbol IF;
    struct TerminalSymbol WHILE;
    struct TerminalSymbol ARRAY;
    struct TerminalSymbol RECORD;
    struct TerminalSymbol CONSTT;
    struct TerminalSymbol INTEGER;
    struct TerminalSymbol BOOLEAN;
    struct TerminalSymbol VAR;
    struct TerminalSymbol PROCEDURE;
    struct TerminalSymbol BEGIN;
    struct TerminalSymbol MODULE;
    struct TerminalSymbol EOFF;
};

void tss_initialize(struct TerminalSymbols *terminalSymbols);

int charIsDigit(char c);

int bothCharIsDigit(char c1, char c2);

int bothCharIsMathSymbol(char c1, char c2);

int charIsASeparatingTerminalSymbol(struct TerminalSymbols terminalSymbols, char symbol);


//__________________________________________________________________________________________________

#endif //OBERONSCOMPILER_B_TERMINALSYMBOLS_H
