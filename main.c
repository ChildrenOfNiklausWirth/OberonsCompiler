#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.h"
#include "Modules/G_CodeGenerator.h"


char executeResult[] = "../execute.txt";
int FLAG_LOAD = 1;
int FLAG_EXECUTABLE = 0;



int main(int argc, char *argv[]) {

    char* inputFile = argv[1];
    char* outputFile = argv[2];

    lexAnalysis(inputFile);
    module();

    
    decode(outputFile);
    
    if (FLAG_EXECUTABLE)
        Exec(executeResult);
    if (FLAG_LOAD)
        Load(executeResult);

    return 0;
}

