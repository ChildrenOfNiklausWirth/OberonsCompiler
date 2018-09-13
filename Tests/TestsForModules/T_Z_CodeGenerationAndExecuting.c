#include <stdlib.h>
#include "../../Modules/CodeGenerator.h"
#include "../../Modules/RISC.h"
#include "../../Modules/LexAnalyzer.h"
#include "../../Modules/SyntaxAnalyzer.h"

void compile(char *inputAddress) {
    FILE *inputFile = fopen(inputAddress, "r");
    FILE *decodedFile = NULL;
    FILE *decodedFileHex = NULL;
    FILE *outputFile = NULL;


    if (inputFile != NULL) {
        lexAnalysis(inputFile, outputFile);
        module();
        decodeHex(decodedFileHex);
        laconicDecode(decodedFile);

        Load(outputFile);


    }
    printf("No such file\n");
}


int test_Loops() {
    char *inputAddress = "../Tests/SamplePrograms/Loops";

    compile(inputAddress);
    printf("Actual\t ");
    longList_print(riscLonglist);
    printf("\n");


    LongList expectedLongList = longList_new();
    longList_add(&expectedLongList, 10);
    longList_add(&expectedLongList, 0);
    longList_add(&expectedLongList, 9);
    longList_add(&expectedLongList, 1);
    longList_add(&expectedLongList, 8);
    longList_add(&expectedLongList, 2);
    longList_add(&expectedLongList, 7);
    longList_add(&expectedLongList, 3);
    longList_add(&expectedLongList, 6);
    longList_add(&expectedLongList, 4);


    printf("Expected ");
    longList_print(expectedLongList);
    printf("\n");
    if (longList_equals(expectedLongList, riscLonglist))
        return 1;
    else
        return 0;

}

int test_Arrays() {

    char *inputAddress = "../Tests/SamplePrograms/Arrays";

    compile(inputAddress);
    printf("Actual\t ");
    longList_print(riscLonglist);
    printf("\n");


    LongList expectedLongList = longList_new();
    longList_add(&expectedLongList, 4);
    longList_add(&expectedLongList, 0);
    longList_add(&expectedLongList, 6);

    printf("Expected ");
    longList_print(expectedLongList);
    printf("\n");
    if (longList_equals(expectedLongList, riscLonglist))
        return 1;
    else
        return 0;
}

int test_Records() {
    char *inputAddress = "../Tests/SamplePrograms/Records";

    compile(inputAddress);
    printf("Actual\t ");
    longList_print(riscLonglist);
    printf("\n");


    LongList expectedLongList = longList_new();
    longList_add(&expectedLongList, 11);
    longList_add(&expectedLongList, 26);
    longList_add(&expectedLongList, 12);
    longList_add(&expectedLongList, 12);
    longList_add(&expectedLongList, 0);
    longList_add(&expectedLongList, 5);

    printf("Expected ");
    longList_print(expectedLongList);
    printf("\n");
    if (longList_equals(expectedLongList, riscLonglist))
        return 1;
    else
        return 0;

}

int test_Conditionals() {

    char *inputAddress = "../Tests/SamplePrograms/Conditionals";

    compile(inputAddress);
    printf("Actual\t ");
    longList_print(riscLonglist);
    printf("\n");


    LongList expectedLongList = longList_new();
    longList_add(&expectedLongList, 2);
    longList_add(&expectedLongList, 3);
    longList_add(&expectedLongList, 4);
    longList_add(&expectedLongList, 5);
    longList_add(&expectedLongList, 6);
    longList_add(&expectedLongList, 5);
    longList_add(&expectedLongList, 7);
    longList_add(&expectedLongList, 7);

    printf("Expected ");
    longList_print(expectedLongList);
    printf("\n");
    if (longList_equals(expectedLongList, riscLonglist))
        return 1;
    else
        return 0;

}



int main() {
    int rightTestDigit = 0;
    int maxTestDigit = 0;

    printf("Loops...\n");
    maxTestDigit++;
    if (test_Loops() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("Arrays...\n");
    maxTestDigit++;
    if (test_Arrays() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("Record...\n");
    maxTestDigit++;
    if (test_Records() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    printf("Condtionals...\n");
    maxTestDigit++;
    if (test_Conditionals() == 1) {
        printf("True\n\n");
        rightTestDigit++;
    } else printf("False\n\n");


    if (rightTestDigit == maxTestDigit)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else printf("\nSOME TESTS FAILED\n\n");

    return 0;
}
