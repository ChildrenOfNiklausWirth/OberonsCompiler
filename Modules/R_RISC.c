#include "R_RISC.h"


bool N, Z;//negative,zero
long R[16];//регистры
long M[(RMemSize / 4) - 1];//ячейки памяти
//FILE W;

void myDecode(unsigned long IR, long *opc, long *a, long *b, long *c) {

    *opc = ((IR >> 26) & ((1 << 6) - 1));

    if (*opc < MOVI) {//F0
        *a = ((IR >> 22) & ((1 << 4) - 1));
        *b = ((IR >> 18) & ((1 << 4) - 1));
        *c = (IR & ((1 << 4) - 1));
        if (*c >= 1 << 3)
            *c -= 1 << 4;
    } else if (*opc < LDW) {//F1
        *a = ((IR >> 22) & ((1 << 4) - 1));
        *b = ((IR >> 18) & ((1 << 4) - 1));
        *c = (IR & ((1 << 18) - 1));
        if (*c >= 1 << 17)
            *c -= 1 << 18;
    } else if (*opc < BEQ) {//F2
        *a = ((IR >> 22) & ((1 << 4) - 1));
        *b = ((IR >> 18) & ((1 << 4) - 1));
        *c = (IR & ((1 << 18) - 1));
        if (*c >= 1 << 17)
            *c -= 1 << 18;
    } else {//F3
        *c = (IR & ((1 << 26) - 1));
        if (*c >= 1 << 25)
            *c -= 1 << 26;

    }


}

void wirthDecode(unsigned long IR, long *opc, long *a, long *b, long *c) {

    *opc = IR / (1 << 26) % (1 << 6);
    *a = IR / (1 << 22) % (1 << 4);
    *b = IR / (1 << 18) % (1 << 4);
    *c = IR % (1 << 4);

    if (*opc < MOVI) {
        *c = R[IR & 0xF];//TODO закомментировать перед запуском T_R_RISC.c
        if (*c >= 1 << 3)
            *c -= 1 << 4;
    } else if (*opc < BEQ) {
        *c = IR % (1 << 18);
        if (*c >= (1 << 17))
            *c -= (1 << 18);
    } else {
        *c = IR % (1 << 26);
        if (*c >= (1 << 25))
            *c -= (1 << 26);
    }

}

void RiscExecute(long start, char *outputAddress) {
    FILE *outputFile = fopen(outputAddress, "w+");

    long IR;//instruction register
    long opc;//Операция
    long nxt;//Указатель
    long a = 0, b = 0, c = 0;//Параметры

    R[14] = 0;
    R[15] = start + ProgOrg;
    bool loop = true;
    while (loop) {
        nxt = R[15] + 4;
        IR = M[R[15] / 4];

        wirthDecode(IR, &opc, &a, &b, &c);
        switch (opc) {
//F0----------------------------------------------------------------------
            case MOV:
                R[a] = c << b;
                break;
            case MVN:
                R[a] = -(c << b);
                break;
            case ADD:
                R[a] = R[b] + c;
                break;
            case SUB:
                R[a] = R[b] - c;
                break;
            case MUL:
                R[a] = R[b] * c;
                break;
            case Div:
                R[a] = R[b] / c;
                break;
            case Mod:
                R[a] = R[b] % c;
                break;
            case CMP:
                Z = (R[b] == c);
                N = R[b] < c;
                break;

//F1----------------------------------------------------------------------
            case MOVI:
                R[a] = c << b;
                break;
            case MVNI:
                R[a] = -(c << b);
            case ADDI:
                R[a] = R[b] + c;
                break;
            case SUBI:
                R[a] = R[b] - c;
                break;
            case MULI:
                R[a] = R[b] * c;
                break;
            case DIVI:
                R[a] = R[b] / c;
                break;
            case MODI:
                R[a] = R[b] % c;
                break;
            case CMPI:
                Z = (R[b] == c);
                N = R[b] < c;
                break;

//F2----------------------------------------------------------------------
            case CHKI:
                if (R[a] < 0 || R[a] >= c)
                    R[a] = 0;
                break;
            case LDW:
                R[a] = M[(R[b] + c) / 4];
                break;
            case LDB:
                //Не реализуется
                break;
            case POP:
                R[a] = M[R[b] / 4];
                R[b] += c;
                break;
            case STW:
                M[(R[b] + c) / 4] = R[a];
                break;
            case STB:
                //не реализуется
                break;
            case PSH:
                R[b] -= c;
                M[R[b] / 4] = R[a];
                break;
            case RD:
                scanf("%li", &R[a]);
                break;
            case WRD:
                //TODO check
                fprintf(outputFile, "%li ", R[c]);
                break;
            case WRH:
                //TODO check
                fprintf(outputFile, " %o", (unsigned int) R[c]);
                break;
            case WRL:
                //TODO check
                fprintf(outputFile, "\n");
                break;

//F3----------------------------------------------------------------------
            case BEQ:
                if (Z)
                    nxt = R[15] + c * 4;
                break;
            case BNE:
                if (!Z)
                    nxt = R[15] + c * 4;
                break;
            case BLT:
                if (N)
                    nxt = R[15] + c * 4;
                break;
            case BGE:
                if (!N)
                    nxt = R[15] + c * 4;
                break;
            case BLE:
                if (Z || N)
                    nxt = R[15] + c * 4;
                break;
            case BGT:
                if (!Z & !N)
                    nxt = R[15] + c * 4;
                break;
            case BR:
                nxt = R[15] + c * 4;
                break;
            case BSR:
                nxt = R[15] + c * 4;
                R[14] = R[15] + 4;
                break;
            case RET:
                nxt = R[c & 0xF];
                if (nxt == 0)
                    loop = false;
                break;
            default:
                printf("Problems with RISC Interpreter");
                break;
        }
        R[15] = nxt;
    }

}

void RiscLoad(const long code[], long len) {

    for (int i = 0; i < len; ++i)
        M[i + ProgOrg / 4] = code[i];

}
