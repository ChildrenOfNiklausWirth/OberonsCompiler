//__________________________________________________________________________________________________

struct TerminalSymbol {
    int condtion;
    char name[20];
    int length;
};

void ts_newTerminalSymbol(struct TerminalSymbol *terminalSymbol, int length, const char *name, int condition) {
    terminalSymbol->length = length;
    terminalSymbol->condtion = condition;

    for (int i = 0; i < length; ++i)
        terminalSymbol->name[i] = name[i];

}

//__________________________________________________________________________________________________

struct TerminalSymbols {
    struct TerminalSymbol terminalSymbols[100];
    int size;
};

void tss_initialize(struct TerminalSymbols *terminalSymbols) {
    terminalSymbols->size = 44;

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
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[26], 6, "number", 34);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[27], 5, "ident", 37);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[28], 1, ";", 38);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[29], 3, "END", 40);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[30], 4, "ELSE", 41);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[31], 6, "ELSEIF", 42);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[32], 2, "IF", 44);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[33], 5, "WHILE", 46);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[34], 5, "ARRAY", 54);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[35], 6, "RECORD", 55);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[36], 5, "CONST", 57);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[37], 7, "INTEGER", 58);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[38], 7, "BOOLEAN", 58);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[39], 3, "VAR", 59);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[40], 9, "PROCEDURE", 60);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[41], 5, "BEGIN", 61);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[42], 6, "MODULE", 63);
    ts_newTerminalSymbol(&terminalSymbols->terminalSymbols[43], 3, "EOF", 64);
}

int charIsDigit(char c) {
    if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' ||
        c == '0')
        return 1;
    return 0;
}

int tss_defineType(struct TerminalSymbols terminalSymbols, struct Token token) {
    int sum = 0;
    for (int i = 0; i < terminalSymbols.size; ++i) {
        if (i == 27)//for variables
            i++;
        if (token.size == terminalSymbols.terminalSymbols[i].length) {
            for (int j = 0; j < token.size; ++j) {
                if (token.symbols[j] == terminalSymbols.terminalSymbols[i].name[j])
                    sum++;

            }

            if (sum == token.size)
                return terminalSymbols.terminalSymbols[i].condtion;
        }

        sum = 0;
    }
    for (int k = 0; k < token.size; ++k) {
        if (charIsDigit(token.symbols[k]))
            sum++;

    }
    if (sum == token.size)
        return 34;


    return 37;

}

int bothCharIsDigit(char c1, char c2) {
    if ((c1 == '0' || c1 == '1' || c1 == '2' ||
         c1 == '3' || c1 == '4' || c1 == '5' ||
         c1 == '6' || c1 == '7' || c1 == '8' || c1 == '9')
        &
        (c2 == '0' ||
         c2 == '1' ||
         c2 == '2' ||
         c2 == '3' ||
         c2 == '4' ||
         c2 == '5' ||
         c2 == '6' ||
         c2 == '7' ||
         c2 == '8' ||
         c2 == '9'))
        return 1;
    return 0;

}

int bothCharIsMathSymbol(char c1, char c2) {
    if ((c1 == '=' || c1 == '<' || c1 == '>' || c1 == ':') & (c2 == '=' || c2 == '<' || c2 == '>' || c2 == ':'))
        return 1;
    return 0;
}

int charIsASeparatingTerminalSymbol(struct TerminalSymbols terminalSymbols, char symbol) {
    for (int i = 0; i < terminalSymbols.size; ++i)
        if (terminalSymbols.terminalSymbols[i].length == 1)
            if (symbol == terminalSymbols.terminalSymbols[i].name[0])
                return 1;
    return 0;
}


//__________________________________________________________________________________________________
