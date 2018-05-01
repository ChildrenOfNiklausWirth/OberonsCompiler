#include <stdio.h>


int charParsing(char *fileName) {
    char c;
    FILE *file = fopen(fileName, "r");
    while (fscanf(file, "%c", &c) != EOF)
        printf("%c", c);


    return 0;
}

