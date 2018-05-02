#include <stdio.h>


struct token {
    char type[10];
    char symbols[50];
    int length;
};

int charParsing(char *fileName) {
    char c;
    FILE *file = fopen(fileName, "r");
    while (fscanf(file, "%c", &c) != EOF)
        printf("%c", c);


    return 0;
}

int wordParsing(char *fileName) {
    struct token tokens[50];
    FILE *file = fopen(fileName, "r");
    char c;
    int currentTokenIndex = 0;

    printf("Original Text\n");
    while (fscanf(file, "%c", &c) != EOF) {
        if (c == ' ' || c == '\n') {
            printf("%c", c);
        } else {
            int index = 0;
            while (c != ' ' && c != '\n' && c != EOF && c != ';') {
                tokens[currentTokenIndex].symbols[index] = c;
                index++;
                printf("%c", c);
                fscanf(file, "%c", &c);

            }
            currentTokenIndex++;
            printf("%c", c);
        }

    }
    printf("\n\nTokens\n\n");
    for (int j = 0; j < currentTokenIndex; ++j) {
        printf("%s\n", tokens[j].symbols);
    }
    return 0;
}
