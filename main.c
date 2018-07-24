#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.c"
#include "Modules/G_CodeGenerator.h"

char firstAdress[] = "../Tests/ProgrammsOnOberon/Trigonometry";



int main() {
    lexAnalysis(firstAdress);
    module();

    cg_initialize();
    decode();
    return 0;
}

