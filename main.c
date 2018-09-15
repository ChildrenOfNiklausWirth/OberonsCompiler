#include <stdlib.h>
#include "Modules/LexAnalyzer.h"
#include "Modules/CodeGenerator.h"
#include "Modules/SyntaxAnalyzer.h"
#ifdef _WIN32
#include <mem.h>
#elif __linux
#include <string.h>
#endif

#define HEAD_INPUT "Programs/Oberon/"
#define HEAD_OUTPUT "Programs/Output/"
#define HEAD_DECODED "Programs/RISCCode/"
#define HEAD_DECODED_HEX "Programs/RISCCodeHex/"


int FLAG_LOAD = 1;
int FLAG_EXECUTABLE = 0;

int main(int argc, char *argv[]) {
    int noArgumentFlag = 0;

    if (argc < 5)
        noArgumentFlag = 1;
//    if (argv[1] == NULL) {
//        printf("Specify input file name");
//        noArgumentFlag = 1;
//    }
//
//    if (argv[2] == NULL) {
//        printf("Specify decoded file name");
//        noArgumentFlag = 1;
//    }
//
//    if (argv[3] == NULL) {
//        printf("Specify decoded file name with HEX addressing");
//        noArgumentFlag = 1;
//    }
//
//    if (argv[4] == NULL) {
//        printf("Specify output file name or set to 0 for stdout");
//        noArgumentFlag = 1;
//    }

    if (noArgumentFlag == 0) {

        char *inputFileName = malloc(sizeof(char) * (strlen(argv[1]) + strlen(HEAD_INPUT) + 1));
        snprintf(inputFileName, (strlen(argv[1]) + strlen(HEAD_INPUT) + 1),"%s%s", HEAD_INPUT, argv[1]);
        char *decodedFileName = malloc(sizeof(char) * (strlen(argv[2]) + strlen(HEAD_DECODED) + 1));
        snprintf(decodedFileName, (strlen(argv[2]) + strlen(HEAD_DECODED) + 1),"%s%s", HEAD_DECODED, argv[2] );
        char *decodedFileNameHex = malloc(sizeof(char) * (strlen(argv[3]) + strlen(HEAD_DECODED_HEX) + 1));
        snprintf(decodedFileNameHex, (strlen(argv[3]) + strlen(HEAD_DECODED_HEX) + 1),"%s%s", HEAD_DECODED_HEX, argv[3] );
        char *outputFileName;

        FILE *inputFile = fopen(inputFileName, "r");
        FILE *decodedFile = fopen(decodedFileName, "w+");
        FILE *decodedFileHex = fopen(decodedFileNameHex, "w+");
        FILE *outputFile = stdout;


//        FILE *inputFile = fopen("../Programs/Oberon/WhileIf", "r");
//        FILE *decodedFile = fopen("../Programs/RISCCode/WhileIf", "w+");
//        FILE *decodedFileHex = fopen("../Programs/RISCCodeHex/WhileIf", "w+");
//        FILE *outputFile = stdout;
//        outputFile = fopen("../Programs/Output/WhileIf", "w+");


        if (strcmp(argv[4], "0") != 0) {
            outputFileName = malloc(sizeof(char) * (strlen(argv[4]) + strlen(HEAD_OUTPUT) + 1));
            snprintf(outputFileName, (strlen(argv[4]) + strlen(HEAD_OUTPUT) + 1),"%s%s", HEAD_OUTPUT, argv[4] );
            outputFile = fopen(outputFileName, "w+");
        } else {
            outputFile = stdout;
        }

        if (inputFile != NULL) {
            lexAnalysis(inputFile, outputFile);
            module();
            decodeHex(decodedFileHex);
            laconicDecode(decodedFile);


            if (FLAG_EXECUTABLE && (syntaxError == 0))
                Exec(outputFile);
            if (FLAG_LOAD && (syntaxError == 0))
                Load(outputFile);
            return 0;
        } else {
            printf("No such file \"%s\"", inputFileName);
        }
    }
    exit(0);
}

