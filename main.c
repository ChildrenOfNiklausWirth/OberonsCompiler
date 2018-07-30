#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.c"
#include "Modules/G_CodeGenerator.h"

char inputAddress[] = "../Tests/ProgrammsOnOberon/Trigonometry";
char outputAddress[] = "../code.txt";


int main() {
    lexAnalysis(inputAddress);
    module();

    cg_initialize();
    decode(outputAddress);
    return 0;
}

