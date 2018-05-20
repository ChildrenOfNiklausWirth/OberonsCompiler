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
    struct TerminalSymbol terminalSymbols[10];
    int size;
};

void tss_initialize(struct TerminalSymbols *terminalSymbols) {
    terminalSymbols->size = 10;

    ts_setName(&terminalSymbols->terminalSymbols[0], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[1], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[2], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[3], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[4], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[5], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[6], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[7], "WHILE", 5);
    ts_setName(&terminalSymbols->terminalSymbols[8], "WHILE", 5);


}

int tss_contains(struct TerminalSymbols terminalSymbols, struct Token token) {
    for (int j = 0; j < terminalSymbols.size; ++j)
        for (int i = 0; i < token.length; ++i)
            if (token.symbols[i] != terminalSymbols.terminalSymbols[j].name[i])
                return 1;

    return 0;

}

//__________________________________________________________________________________________________

