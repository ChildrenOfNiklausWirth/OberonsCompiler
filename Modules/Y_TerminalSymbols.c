//__________________________________________________________________________________________________

struct TerminalSymbol {
    int condtion;
    char name[6];
    int length;
};

void ts_newTerminalSymbol(struct TerminalSymbol *terminalSymbol, int length, const char *name, int condition) {
    terminalSymbol->length = length;

    for (int i = 0; i < length; ++i)
        terminalSymbol->name[i] = name[i];

}

//__________________________________________________________________________________________________

struct TerminalSymbols {
    struct TerminalSymbol terminalSymbols[52];
    int size;
};

void tss_initialize(struct TerminalSymbols *terminalSymbols) {
    terminalSymbols->size = 52;

    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[0], 4, "NULL", 0);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[1], 1, "*", 1);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[2], 1, "/", 3);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[3], 3, "MOD", 4);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[4], 3, "AND", 5);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[5], 1, "+", 6);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[6], 1, "-", 7);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[7], 1, "&", 8);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[8], 1, "=", 9);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[9], 1, "#", 10);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[10], 1, "<", 11);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[11], 2, ">=", 12);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[12], 2, "<=", 13);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[13], 1, ">", 14);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[14], 1, ".", 18);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[15], 1, ",", 19);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[16], 1, ":", 20);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[17], 1, ")", 22);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[18], 1, "]", 23);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[19], 2, "DO", 25);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[20], 4, "THEN", 26);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[21], 2, "DO", 27);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[22], 1, "(", 29);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[23], 1, "[", 30);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[24], 1, "`", 32);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[25], 2, ":=", 33);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[26], 1, "0", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[27], 1, "1", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[28], 1, "2", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[29], 1, "3", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[30], 1, "4", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[31], 1, "5", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[32], 1, "6", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[33], 1, "7", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[34], 1, "8", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[35], 1, "9", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[36], 5, "ident", 37);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[37], 1, ";", 38);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[38], 3, "AND", 40);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[39], 4, "ELSE", 41);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[40], 6, "ELSEIF", 42);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[41], 2, "IF", 44);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[42], 5, "WHILE", 46);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[43], 5, "ARRAY", 54);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[44], 6, "RECORD", 55);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[45], 5, "CONST", 57);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[46], 4, "TYPE", 58);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[47], 3, "VAR", 59);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[48], 9, "PROCEDURE", 60);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[49], 5, "BEGIN", 61);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[50], 6, "MODULE", 63);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[51], 3, "EOF", 64);
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

