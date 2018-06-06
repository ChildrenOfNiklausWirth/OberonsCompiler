#ifndef OBERONSCOMPILER_B_TERMINALSYMBOLS_H
#define OBERONSCOMPILER_B_TERMINALSYMBOLS_H

#include "A_Tokens_And_DV.h"


struct TerminalSymbol {
    int condtion;
    char name[20];
    int length;
};

void ts_newTerminalSymbol(struct TerminalSymbol *terminalSymbol, int length, const char *name, int condition);

//__________________________________________________________________________________________________

const int TS_SIZE;
struct TerminalSymbols {
    struct TerminalSymbol terminalSymbols[44];
    int size;
};

void tss_initialize(struct TerminalSymbols *terminalSymbols);

int charIsDigit(char c);

int tss_defineType(struct TerminalSymbols terminalSymbols, struct Token token);

int bothCharIsDigit(char c1, char c2);

int bothCharIsMathSymbol(char c1, char c2);

int charIsASeparatingTerminalSymbol(struct TerminalSymbols terminalSymbols, char symbol);


//__________________________________________________________________________________________________

#endif //OBERONSCOMPILER_B_TERMINALSYMBOLS_H
