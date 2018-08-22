#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.c"
#include "Modules/G_CodeGenerator.h"

char inputAddress[] = "../Tests/ProgrammsOnOberon/Procedures";
char outputAddress[] = "../code.txt";


int main(int argc, char *argv[]) {

    char* inputFile = argv[1];
    char* outputFile = argv[2];

    lexAnalysis(inputFile);
    module();

    cg_initialize();
    decode(outputFile);
    return 0;
}

