#include "Modules/B_LexAnalyzer.h"
#include "Modules/C_SyntaxAnalyzer.h"
#include "Modules/G_CodeGenerator.h"

char oberonCode[] = "../Tests/ProgrammsOnOberon/1_SimpleProgram.txt";
char codeGeneratorResult[] = "../code.txt";
char executeResult[] = "../execute.txt";

int FLAG_LOAD = 1;
int FLAG_EXECUTABLE = 0;

int main() {
    lexAnalysis(oberonCode);

    module();

    decode(codeGeneratorResult);

    if (FLAG_EXECUTABLE)
        Exec(executeResult);
    if (FLAG_LOAD)
        Load(executeResult);

    return 0;
}

