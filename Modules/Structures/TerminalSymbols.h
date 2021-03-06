#ifndef OBERONSCOMPILER_B_TERMINALSYMBOLS_H
#define OBERONSCOMPILER_B_TERMINALSYMBOLS_H

struct TerminalSymbol {
    char *name;
    int nameLength;
    int type;
};

struct TerminalSymbol ts_newTerminalSymbol(char name[], int nameLength, int type);

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
    struct TerminalSymbol ARR;
    struct TerminalSymbol REC;
    struct TerminalSymbol CONSTT;
    struct TerminalSymbol INT;
    struct TerminalSymbol BOOL;
    struct TerminalSymbol TYPE;
    struct TerminalSymbol VAR;
    struct TerminalSymbol PROCEDURE;
    struct TerminalSymbol BEGIN;
    struct TerminalSymbol MODULE;
    struct TerminalSymbol EOFF;
} terminalSymbols;

void tss_initialize(struct TerminalSymbols *terminalSymbols);

#endif //OBERONSCOMPILER_B_TERMINALSYMBOLS_H
