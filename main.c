#include <stdlib.h>
#include <memory.h>
#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.h"
#include "Modules/G_CodeGenerator.h"

int FLAG_LOAD = 1;
int FLAG_EXECUTABLE = 0;



int main(int argc, char *argv[]) {

    char *inputFileName = argv[1];
    char *decodedFileName = argv[2];
    char *outputFileName = argv[3];
    int  errflag = 0;


    if (inputFileName == NULL) {
        printf("Specify input file name");
        errflag = 1;
    }

    if (decodedFileName == NULL) {
        printf("Specify decoded file name");
        errflag = 1;
    }

    if (outputFileName == NULL) {
        printf("Specify output file name or set to 0 for stdout");
        errflag = 1;
    }

    if (errflag == 0) {
        FILE* inputFile = fopen(inputFileName, "r");
        FILE* decodedFile = fopen(decodedFileName, "w+");
        FILE* outputFile = stdout;

        if (strcmp(outputFileName, "0") != 0) {
            outputFile = fopen(outputFileName, "w+");
        }

        if (inputFile != NULL) {
            lexAnalysis(inputFile);
            module();
            decode(decodedFile);

            if (FLAG_EXECUTABLE)
                Exec(outputFile);
            if (FLAG_LOAD)
                Load(outputFile);
            return 0;

        } else {
            printf("No such file \"%s\"", inputFileName);
        }
    }
}

