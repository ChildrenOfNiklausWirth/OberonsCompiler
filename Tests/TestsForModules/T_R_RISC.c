#include "../../Modules/SimpleFunctions/SimpleFunctions.h"
#include "../../Modules/R_RISC.h"
#include "../../Modules/G_CodeGenerator.h"

enum Report {
    REPORT,//Test with report
    NO_REPORT,//Test without report
    NO_WORK//Test just returns 1
};
int maxMessageLength;
int currentMessageLength;
char *message;

//-----------------------------------------------------------------------------------------------
void message_initialize() {
    maxMessageLength = 10;
    currentMessageLength = 0;
    message = calloc((size_t) maxMessageLength, sizeof(char));
}

void message_add(char testNumber) {
    char newMess[] = "Error in test number ";

    if ((currentMessageLength + sizeof(newMess) - 1) >= maxMessageLength) {
        maxMessageLength = currentMessageLength + sizeof(newMess) + 1;
        message = realloc(message, (size_t) maxMessageLength);
    }

    for (int i = 0; i < sizeof(newMess) - 1; ++i) {
        message[currentMessageLength] = newMess[i];
        currentMessageLength++;
    }
    message[currentMessageLength] = testNumber;
    currentMessageLength++;
    message[currentMessageLength] = '\n';
    currentMessageLength++;

}

void message_print() {
    for (int i = 0; i < currentMessageLength; ++i)
        printf("%c", message[i]);
    printf("\n");

}
//-----------------------------------------------------------------------------------------------

int decodingTest(enum Report report, long op, long a, long b, long c) {
    if (report != NO_WORK) {
        unsigned long IR;
        //encoding
        if (op > WRL)
            IR = encodeF3(op, c);
        else
            IR = encode(op, a, b, c);

        if (report == REPORT) {
            printf("\nBinary digit after encoding \n");
            binaryPrint(IR);
            printf("\nDecimal form\n");
            printf("%lu\n", IR);
            printf("\nBinary digit that we multiply with c\n");
            binaryPrint(int_hexToDecimal(40000));
        }
        //my decode
        long mop, ma, mb, mc;
        myDecode(IR, &mop, &ma, &mb, &mc);
        //wirth decode
        long wop, wa, wb, wc;
        wirthDecode(IR, &wop, &wa, &wb, &wc);

        //Report
        if (report == REPORT) {
            printf("\nComparison\n\n");
            printf("\tEncode \t\tMy decode \tWirth decode\n");
            printf("op \t%li \t\t%li \t\t%li\n", op, mop, wop);
            printf("a \t%li \t\t%li \t\t%li\n", a, ma, wa);
            printf("b \t%li \t\t%li \t\t%li\n", b, mb, wb);
            printf("c \t%li \t\t%li \t\t%li\n", c, mc, wc);
        }
        if ((op == wop && wop == mop) && (a == wa && wa == ma) && (b == wb && wb == mb) && (c == wc && wc == mc))
            return 1;
        return 0;
    }
    return 1;


}

int main() {
    printf("RISC Testing...\n\n");
    int maxTests = 2;
    int passedTest = 0;
    message_initialize();

    printf("-----------------------------------1 TEST-------------------------------------------------------\n");
    if (decodingTest(REPORT, STW, 5, 0, 16)) {
        passedTest++;
        printf("\nTRUE\n");
    } else
        message_add('1');


    printf("\n-----------------------------------2 TEST-------------------------------------------------------\n");
    if (decodingTest(NO_WORK, STW, 5, 0, -16)) {
        passedTest++;
        printf("\nTRUE\n");
    } else
        message_add('2');



    printf("\n-----------------------------------REPORT-------------------------------------------------------\n");
    if (maxTests == passedTest)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else {
        printf("\nSOME TESTS FAILED\n\n");
        message_print();
    }


    return 1;
}