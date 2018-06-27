#ifndef OBERONSCOMPILER_C_C_SYNTAXANALYZER_H
#define OBERONSCOMPILER_C_C_SYNTAXANALYZER_H
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include "Structures/B_TerminalSymbols.h"
#include "Structures/A_Tokens.h"
#include "B_LexAnalyzer.h"
#include "Structures/Object.h"
#include "G_CodeGenerator.h"


void module() {
    char *modid;
    if (tf_next(&tokensFlow).type == terminalSymbols.MODULE.type) {
        tf_next(&tokensFlow);
        Open();
        openScope();
        long varsize = 0;
        if (tokensFlow.current.type == terminalSymbols.IDENT.type) {
            modid = tokensFlow.current.symbols;
            tf_next(&tokensFlow);
        } else {
            printf("ident?");
        }

        if (tf_next(&tokensFlow).type == terminalSymbols.SEMICOLON.type) {
            tf_next(&tokensFlow);
        } else {
            Mark(";?");
        }

        varsize += declarations();

        while (tokensFlow.current.type == terminalSymbols.PROCEDURE.type) {
            procedureDeclaration();
            if (tokensFlow.current.type == terminalSymbols.SEMICOLON.type)
                tf_next(&tokensFlow);
            else
                Mark(";?");
        }

        Header(varsize);
        if (tokensFlow.current.type == terminalSymbols.BEGIN.type) {
            tf_next(&tokensFlow);
            StatSequence();
        }
        if (tokensFlow.current.type == terminalSymbols.END.type) {
            tf_next(&tokensFlow);

        } else
            Mark("End?");
        if (tokensFlow.current.type == terminalSymbols.IDENT.type) {
            //TODO
            if (modid != tokensFlow.current.symbols) {
                Mark("не подходит");
            }
            tf_next(&tokensFlow);

        } else
            Mark("идентефикатор");
        if (tokensFlow.current.type != terminalSymbols.PERIOD.type) {
            Mark(".?");
        }
        closeScope();

    } else
        Mark("Модуль?");


}

#endif //OBERONSCOMPILER_C_C_SYNTAXANALYZER_H
