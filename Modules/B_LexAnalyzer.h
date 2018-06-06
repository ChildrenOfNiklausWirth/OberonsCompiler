#ifndef OBERONSCOMPILER_B_LEKSANALYZER_H
#define OBERONSCOMPILER_B_LEKSANALYZER_H
#include <stdio.h>
#include "Structures/A_Tokens_And_DV.h"
#include "Structures/B_TerminalSymbols.h"


struct TerminalSymbols terminalSymbols;

struct Token readNextToken(FILE *file, char currentSymbol);

void lexAnalysis(char *fileName, struct TokensFlow *tokensFlow);

#endif //OBERONSCOMPILER_B_LEKSANALYZER_H
