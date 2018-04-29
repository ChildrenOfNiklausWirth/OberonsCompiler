#include <stdio.h>



int parsing(char fileName[]) {

    FILE *file = fopen(fileName, "r");

    char symbol[80];
    int i = 0;

    while (fscanf(file, "%s", symbol) != EOF) {
        printf("%s \n", symbol);
        i++;
    }
    printf("%d",i);
    return 0;
}

