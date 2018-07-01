#ifndef OBERONSCOMPILER_B_LEKSANALYZER_H
#define OBERONSCOMPILER_B_LEKSANALYZER_H

#include <stdio.h>
#include "Structures/A_Tokens.h"
#include "Structures/B_TerminalSymbols.h"

//D
extern struct TerminalSymbols terminalSymbols; //need to be initialised with ts_initialise
extern struct TokensFlow syntaxTokensFlow; //need to be created with lexAnalysis

int readNextToken(FILE *file, Token *token);

void lexAnalysis(char *fileName);

void Mark(char msg[]);

#endif //OBERONSCOMPILER_B_LEKSANALYZER_H
