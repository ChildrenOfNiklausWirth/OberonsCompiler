#ifndef OBERONSCOMPILER_B_LEKSANALYZER_H
#define OBERONSCOMPILER_B_LEKSANALYZER_H

#include <stdio.h>
#include "Structures/A_Tokens.h"
#include "Structures/B_TerminalSymbols.h"


struct TerminalSymbols terminalSymbols;
struct TokensFlow tokensFlow;

struct Token readNextToken(FILE *file, char currentSymbol);

void lexAnalysis(char *fileName);

void Mark(char msg[]);

#endif //OBERONSCOMPILER_B_LEKSANALYZER_H
