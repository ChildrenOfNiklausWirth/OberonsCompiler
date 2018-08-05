#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.c"
#include "Modules/G_CodeGenerator.h"

char oberonCode[] = "../Tests/ProgrammsOnOberon/Trigonometry";
char codeGeneratorResult[] = "../code.txt";
char executeResult[] = "../execute.txt";

int FLAG_EXECUTABLE = 1;

int main() {
    lexAnalysis(oberonCode);

    module();

    decode(codeGeneratorResult);

    if (FLAG_EXECUTABLE) {
        Load(executeResult);
        Exec(executeResult);
    }


    return 0;
}

