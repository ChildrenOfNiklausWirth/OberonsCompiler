#include "../../Modules/SimpleFunctions/SimpleFunctions.h"
#include "../../Modules/RISC.h"
#include "../../Modules/CodeGenerator.h"

enum Report {
    REPORT,//Test with report
    ONLY_ERROR,
    NO_REPORT
};

//-----------------------------------------------------------------------------------------------
void printOperation(int op) {
    switch (op) {
        //F0
        case MOV:
            printf("%s", "MOV : ");
            break;
        case MVN:
            printf("%s", "MVN : ");
            break;
        case ADD :
            printf("%s", "ADD : ");
            break;
        case SUB :
            printf("%s", "SUB : ");
            break;
        case MUL :
            printf("%s", "MUL : ");
            break;
        case Div :
            printf("%s", "DIV : ");
            break;
        case Mod :
            printf("%s", "MOD : ");
            break;
        case CMP :
            printf("%s", "CMP : ");
            break;

//F1
        case MOVI :
            printf("%s", "MOVI : ");
            break;
        case MVNI :
            printf("%s", "MVNI : ");
            break;
        case ADDI :
            printf("%s", "ADDI : ");
            break;
        case SUBI :
            printf("%s", "SUBI : ");
            break;
        case MULI :
            printf("%s", "MULI : ");
            break;
        case DIVI :
            printf("%s", "DIVI : ");
            break;
        case MODI :
            printf("%s", "MODI : ");
            break;
        case CMPI :
            printf("%s", "CMPI : ");
            break;
        case CHKI :
            printf("%s", "CHKI : ");
            break;

//F2
        case LDW :
            printf("%s", "LDW : ");
            break;
        case LDB :
            printf("%s", "LDB : ");
            break;
        case POP :
            printf("%s", "POP : ");
            break;
        case STW :
            printf("%s", "STW : ");
            break;
        case STB :
            printf("%s", "STB : ");
            break;
        case PSH :
            printf("%s", "PSH : ");
            break;
        case RD :
            printf("%s", "RD : ");
            break;
        case WRD :
            printf("%s", "WRD : ");
            break;
        case WRH :
            printf("%s", "WRH : ");
            break;
        case WRL :
            printf("%s", "WRL : ");
            break;

//F3
        case BEQ :
            printf("%s", "BEQ : ");
            break;
        case BNE :
            printf("%s", "BNE : ");
            break;
        case BLT :
            printf("%s", "BLT : ");
            break;
        case BGE :
            printf("%s", "BGE : ");
            break;
        case BLE :
            printf("%s", "BLE : ");
            break;
        case BGT :
            printf("%s", "BGT : ");
            break;
        case BR :
            printf("%s", "BR : ");
            break;
        case BSR :
            printf("%s", "BSR : ");
            break;
        case RET :
            printf("%s", "RET : ");
            break;
        default:
            printf("%s", "Case isn't defined");

    }
}

void printReport(unsigned int IR, int op, int a, int b, int c,
                 int mop,  int ma, int mb, int mc, int wop, int wa, int wb, int wc) {
    printf("---------------------------------------\n");
    printf("\nBinary digit after encoding \n");
    binaryPrint((long) IR);
    printf("\nDecimal form\n");
    printf("%d\n", IR);
    printf("\nComparison\n\n");
    printf("\tEncode \t\tMy decode \tWirth decode\n");
    printf("op \t%d \t\t%d \t\t%d\n", op, mop, wop);
    printf("a \t%d \t\t%d \t\t%d\n", a, ma, wa);
    printf("b \t%d \t\t%d \t\t%d\n", b, mb, wb);
    printf("c \t%d \t\t%d \t\t%d\n", c, mc, wc);


}

int decodingTest(enum Report report, int op, int a, int b, int c) {
    int IR;
    //encoding
    if (op > WRL)
        IR = encodeF3(op, c);
    else
        IR = encode(op, a, b, c);

    //my decode
    int  mop, ma, mb, mc;
    myDecode((unsigned int) IR, (unsigned int *) &mop, &ma, &mb, &mc);
    //wirth decode
    int wop, wa, wb, wc;
    wirthDecode((unsigned int) IR, &wop, &wa, &wb, &wc);

    if (op > WRL) {
        if ((op == wop && wop == mop) && (c == wc && wc == mc)) {
            if (report == REPORT)
                printReport((unsigned int) IR, op, a, b, c, mop, ma, mb, mc, wop, wa, wb, wc);
            return 1;
        }
    } else {
        if ((op == wop && wop == mop) && (a == wa && wa == ma) && (b == wb && wb == mb) &&
            (c == wc && wc == mc)) {
            if (report == REPORT)
                printReport((unsigned int) IR, op, a, b, c, mop, ma, mb, mc, wop, wa, wb, wc);
            return 1;
        }
    }
    if (report == ONLY_ERROR)
        printReport((unsigned int) IR, op, a, b, c, mop, ma, mb, mc, wop, wa, wb, wc);
    return 0;


}

int opTest(enum Report report, long op, long minA, long maxA, long minB, long maxB, long minC, long maxC) {
    for (int a = minA; a < maxA; ++a)
        for (int b = minB; b < maxB; ++b)
            for (int c = minC; c < maxC; ++c)
                if (!decodingTest(report, op, a, b, c))
                    return 0;
    return 1;

}


int main() {
    printf("RISC Testing...\n\n");
    int maxTests = 0;
    int passedTest = 0;

    printf("-----------------------------------F0 Testing-------------------------------------------------------\n");
    maxTests += 8;
    for (int op = 0; op <= 7; ++op) {
        if (opTest(ONLY_ERROR, op, 0, 1 << 4, 0, 1 << 4, -(1 << 3), 1 << 3)) {
            passedTest++;
            printOperation(op);
            printf("TRUE\n");
        } else {
            printOperation(op);
            printf("FALSE\n");
        }
    }

    printf("-----------------------------------F1 Testing-------------------------------------------------------\n");
    maxTests += (25 - 16);
    for (int op = 16; op <= 24; ++op) {
        if (opTest(ONLY_ERROR, op, 0, 1 << 4, 0, 1 << 4, -(1 << 7), 1 << 8)) {
            passedTest++;
            printOperation(op);
            printf("TRUE\n");
        } else {
            printOperation(op);
            printf("FALSE\n");
        }
    }

    printf("-----------------------------------F2 Testing-------------------------------------------------------\n");
    maxTests += (44 - 32 - 2);
    for (int op = 32; op <= 43; ++op) {
        if (op != 35 && op != 39)
            if (opTest(ONLY_ERROR, op, 0, 1 << 4, 0, 1 << 4, -(1 << 7), 1 << 8)) {
                passedTest++;
                printOperation(op);
                printf("TRUE\n");
            } else {
                printOperation(op);
                printf("FALSE\n");
            }
    }
    printf("-----------------------------------F3 Testing-------------------------------------------------------\n");
    maxTests += (59 - 48 - 2);
    for (int op = 48; op <= 58; ++op) {
        if (op != 54 && op != 55)
            if (opTest(ONLY_ERROR, op, 0, 1 << 4, 0, 1 << 4, 0, 1 << 13)) {//TODO �������� ��������� minC<0
                passedTest++;
                printOperation(op);
                printf("TRUE\n");
            } else {
                printOperation(op);
                printf("FALSE\n");
            }
    }


    printf("\n-----------------------------------REPORT-------------------------------------------------------\n");
    if (maxTests == passedTest)
        printf("\nALL TESTS WAS SUCCESSFULLY\n\n");
    else {
        printf("\nSOME TESTS FAILED\nMAYBE FORGOT REMOVE SOMETHING\n");
    }

    return 1;
}