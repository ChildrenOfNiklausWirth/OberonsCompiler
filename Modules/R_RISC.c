#include "R_RISC.h"


long IR;//instruction register
bool N, Z;//negative,zero
long R[16];//регистры
long M[MemSize / 4];//ячейки памяти
//FILE W;

void RiscExecute(long start, char *outputAddress) {
    FILE *outputFile = fopen(outputAddress, "w+");

    int opc;//Операция
    long nxt;//Указатель
    long a = 0, b = 0, c = 0;//Параметры

    R[14] = 0;
    R[15] = start + ProgOrg;
    bool loop = true;
    while (loop) {
        nxt = R[15] + 4;
        IR = M[R[15] / 4];

        opc = (IR >> 26) & 63;

        if (opc < F1) {//F0
            a = (IR >> 22) & 15;
            b = (IR >> 18) & 15;
            c = IR & 15;
        } else if (opc < F2) {//F1
            a = (IR >> 22) & 15;
            b = (IR >> 18) & 15;
            c = IR & 262143;
        } else if (opc < F3) {//F2
            a = (IR >> 22) & 15;
            b = (IR >> 18) & 15;
            c = IR & 262143;
        } else {//F3
            c = IR & 67108863;
        }


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
                fprintf(outputFile, " %li %d", R[c], 1);
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
                nxt = R[c % int_hexToDecimal(10)];
                if (nxt == 0)
                    loop = false;
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
