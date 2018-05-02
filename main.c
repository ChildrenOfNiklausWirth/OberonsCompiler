#include "C:\Users\Danila Eremenko\CLionProjects\OberonsCompiler\Modules\A_Parser.c"

char adress[] = "C:\\Users\\Danila Eremenko\\CLionProjects\\OberonsCompiler\\Tests\\CompilerTests\\1_Test.txt";
struct Token tokens[50];
int tokensDigit;

void printTokens() {
    for (int i = 0; i < tokensDigit; ++i) {
        for (int j = 0; j < tokens[i].length; ++j) {
            printf("%c", tokens[i].symbols[j]);
        }
        printf("\n");
        tokens;

    }
}

int main() {
    leksParser(adress, (struct Token *) &tokens, &tokensDigit);
    printTokens();

    return 0;
}

