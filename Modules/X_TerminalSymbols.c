struct TerminalSymbol {
    char name[6];
    int length;
};

void ts_setName(struct TerminalSymbol *terminalSymbol, const char name[], int length) {
    terminalSymbol->length = length;

    for (int i = 0; i < length; ++i)
        terminalSymbol->name[i] = name[i];

}

//__________________________________________________________________________________________________

struct TerminalSymbols {
    struct TerminalSymbol terminalSymbols[21];
    int size;
};

void tss_initialize(struct TerminalSymbols *terminalSymbols) {
    terminalSymbols->size = 21;

    ts_setName(&terminalSymbols->terminalSymbols[0], "0", 1);
    ts_setName(&terminalSymbols->terminalSymbols[1], "1", 1);
    ts_setName(&terminalSymbols->terminalSymbols[2], "2", 1);
    ts_setName(&terminalSymbols->terminalSymbols[3], "3", 1);
    ts_setName(&terminalSymbols->terminalSymbols[4], "4", 1);
    ts_setName(&terminalSymbols->terminalSymbols[5], "5", 1);
    ts_setName(&terminalSymbols->terminalSymbols[6], "6", 1);
    ts_setName(&terminalSymbols->terminalSymbols[7], "7", 1);
    ts_setName(&terminalSymbols->terminalSymbols[8], "8", 1);
    ts_setName(&terminalSymbols->terminalSymbols[9], "9", 1);
    ts_setName(&terminalSymbols->terminalSymbols[10], "+", 1);
    ts_setName(&terminalSymbols->terminalSymbols[11], "-", 1);
    ts_setName(&terminalSymbols->terminalSymbols[12], "/", 1);
    ts_setName(&terminalSymbols->terminalSymbols[13], "*", 1);
    ts_setName(&terminalSymbols->terminalSymbols[14], "=", 1);
    ts_setName(&terminalSymbols->terminalSymbols[15], "VAR", 3);
    ts_setName(&terminalSymbols->terminalSymbols[16], "INTEGER", 7);
    ts_setName(&terminalSymbols->terminalSymbols[17], "IF", 2);
    ts_setName(&terminalSymbols->terminalSymbols[18], "END", 3);
    ts_setName(&terminalSymbols->terminalSymbols[19], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[20], "MODULE", 6);


}

int tss_containsToken(struct TerminalSymbols terminalSymbols, struct Token token) {
    int sum = 0;
    for (int i = 0; i < terminalSymbols.size; ++i) {
        if (token.length == terminalSymbols.terminalSymbols[i].length) {
            for (int j = 0; j < token.length; ++j)
                if (token.symbols[j] == terminalSymbols.terminalSymbols[i].name[j])
                    sum++;

            if (sum == token.length)
                return 1;
        }

        sum = 0;
    }


    return 0;

}

int tss_containsChar(struct TerminalSymbols terminalSymbols, char symbol) {
    for (int i = 10; i < 15; ++i)
        if (symbol == terminalSymbols.terminalSymbols[i].name[0])
            return 1;
    return 0;


}

//__________________________________________________________________________________________________

