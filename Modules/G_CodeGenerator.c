#include "G_CodeGenerator.h"

//int MemSize = 1024;
Ident *comname[NUMBER_OF_COMMANDS];
long comaddr[NUMBER_OF_COMMANDS];
char *mnemo[64];
unsigned long code[MAXCODE];
Type intType = {INTEGER, 0, 0, 4, 0};
Type boolType = {BOOLEAN, 0, 0, 4, 0};


//CALL BEFORE USING FUNCTIONS
void cg_initialize() {

    for (int i = 0; i < 64; ++i) {
        mnemo[i] = calloc(5, sizeof(char));
    }

    mnemo[MOV] = "MOV";
    mnemo[MVN] = "MVN";
    mnemo[ADD] = "ADD";
    mnemo[SUB] = "SUB";
    mnemo[MUL] = "MUL";
    mnemo[DIVIDE] = "DIV";
    mnemo[MODULUS] = "MOD";
    mnemo[CMP] = "CMP";
    mnemo[MOVI] = "MOVI";
    mnemo[MVNI] = "MVNI";
    mnemo[ADDI] = "ADDI";
    mnemo[SUBI] = "SUBI";
    mnemo[MULI] = "MULI";
    mnemo[DIVI] = "DIVI";
    mnemo[MODI] = "MODI";
    mnemo[CMPI] = "CMPI";
    mnemo[CHKI] = "CHKI";
    mnemo[LDW] = "LDW";
    mnemo[LDB] = "LDB";
    mnemo[POP] = "POP";
    mnemo[STW] = "STW";
    mnemo[STB] = "STB";
    mnemo[PSH] = "PSH";
    mnemo[BEQ] = "BEQ";
    mnemo[BNE] = "BNE";
    mnemo[BLT] = "BLT";
    mnemo[BGE] = "BGE";
    mnemo[BLE] = "BLE";
    mnemo[BGT] = "BGT";
    mnemo[BR] = "BR";
    mnemo[BSR] = "BSR";
    mnemo[RET] = "RET";
    mnemo[RD] = "READ";
    mnemo[WRD] = "WRD";
    mnemo[WRH] = "WRH";
    mnemo[WRL] = "WRL";
}

//Возвращает свободный регистр
long GetReg() {
    int i = 0;
    while ((i < FP) && (set_contains(*regs, i)))
        i++;
    set_INCL(regs, i);
    return i;
}

//Генерирует команды форматов F0,F1,F2
void Put(long op, long a, long b, long c) {
    if (op >= 32)
        op -= 64;
    code[pc] = (((((op << 4) | a) << 4) | b) << 18) | (c & 0x3FFFF);
    pc++;
}

//Генерирует команды формата F3
void PutBR(long op, long disp) {
    code[pc] = (op - 0x40) << 26 | (disp & 0x3FFFFFF);
    pc++;
}

void TestRange(long x) {
    if ((x >= int_hexToDecimal(20000)) || (x < int_hexToDecimal(-20000)))
        Mark("Value is out of range");

}

//Загружает переменную или константу в code[ ]
struct Item load(struct Item *x) {
    long r;
    if (x->mode == VARIABLE) {
        if (x->level == 0)
            x->a = x->a - pc * 4;
        r = GetReg();
        Put(LDW, r, x->r, x->a);
        set_EXCL(regs, x->r);
        x->r = r;
    } else if (x->mode == CONST) {
        TestRange(x->a);
        x->r = GetReg();
        Put(MOVI, x->r, 0, x->a);
    }
    x->mode = REG;
}

struct Item loadBool(struct Item *x) {
    if (x->type->form != BOOLEAN)
        Mark("Boolean?");
    load(x);
    x->mode = COND;
    x->a = 0;
    x->b = 0;
    x->c = 1;
}

//Генерирует операцию с двумя операндами
void PutOp(long operation, struct Item *x, struct Item *y) {
    if (x->mode != REG)
        load(x);
    if (y->mode == CONST) {
        TestRange(y->a);
        Put(operation + 16, x->r, x->r, y->a);
    } else {
        if (y->mode != REG)
            load(y);
        Put(operation, x->r, x->r, y->r);
        set_EXCL(regs, y->r);
    }
}

long negated(long cond) {
    if (cond % 2 == 1)
        return cond - 1;
    else
        return cond + 1;
}

long merged(long L0, long L1) {
    long L2, L3;
    if (L0 != 0) {
        L2 = L0;
        while (1) {
            L3 = code[L2] % int_hexToDecimal(40000);
            if (L3 == 0)
                break;
            L2 = L3;
        }
        code[L2] = code[L2] - L3 + L1;
        return L0;
    } else
        return L1;
}

void fix(long at, long with) {
    code[at] = code[at] / int_hexToDecimal(400000) * int_hexToDecimal(400000) + with % int_hexToDecimal(400000);
}

long fixWith(long L0, long L1) {
    long L2;
    while (L0 != 0) {
        L2 = code[L0] % int_hexToDecimal(40000);
        fix(L0, L1 - L0);
        L0 = L2;
    }
    return L0;

}

long FixLink(long L) {
    long L1;
    while (L != 0) {
        L1 = code[L] % int_hexToDecimal(40000);
        fix(L, pc - L);
        L = L1;
    }
}

void IncLevel(int n) {
    curlev += n;
}

void MakeConstltem(struct Item *x, Type *typ, long val) {
    x->mode = CONST;
    x->type = typ;
    x->a = val;
}

//Создает Item на основе Node
void MakeItem(struct Item *x, Node *y) {
    long r;

    x->mode = y->class;
    x->type = y->type;
    x->level = y->level;
    x->a = y->val;
    x->b = 0;

    if (y->level == 0) {
        x->r = PC;
    } else if (y->level == curlev)
        x->r = FP;
    else {
        Mark("Level mismatch!");
        x->r = 0;
    }
    if (y->class == PAR) {
        r = GetReg();
        Put(LDW, r, x->r, x->a);
        x->mode = VARIABLE;
        x->r = r;
        x->a = 0;
    }
}

void Field(struct Item *x, Node *y) {
    x->a += y->val;
    x->type = y->type;
}

void Index(struct Item *x, struct Item *y) {
    if (y->type != &intType)
        Mark("Index isn't integer");
    if (y->mode == CONST) {
        if ((y->a < 0) || (y->a >= x->type->len))
            Mark("Wrong index");
    } else {
        if (y->mode != REG)
            load(y);
        Put(CHKI, y->r, 0, x->type->len);
        Put(MULI, y->r, y->r, x->type->base->size);
        Put(ADD, y->r, x->r, y->r);
        set_EXCL(regs, x->r);
        x->r = y->r;
    }
    x->type = x->type->base;
}

void Op1(int op, struct Item *x) {
    long t;
    if (op == terminalSymbols.MINUS.type)
        if (x->type->form != INTEGER) {
            Mark("Type mismatch");
        } else if (x->mode == CONST) {
            x->a = -x->a;
        } else {
            if (x->mode == VARIABLE)
                load(x);
            Put(MVN, x->r, 0, x->r);
        }
    else if (op == terminalSymbols.NOT.type) {
        if (x->mode != COND) {
            loadBool(x);
        }
        x->c = negated(x->c);
        t = x->a;
        x->a = x->b;
        x->b = t;
    } else if (op == terminalSymbols.AND.type) {
        if (x->mode != COND)
            loadBool(x);
        PutBR(BEQ + negated(x->c), x->a);
        set_EXCL(regs, x->r);
        x->a = pc - 1;
        FixLink(x->b);
        x->b = 0;
    } else if (op == terminalSymbols.OR.type) {
        if (x->mode != COND)
            loadBool(x);
        PutBR(BEQ + x->c, x->b);
        set_EXCL(regs, x->r);
        x->b = pc - 1;
        FixLink(x->a);
        x->a = 0;
    }

}

void Op2(int op, struct Item *x, struct Item *y) {
    if ((x->type->form == INTEGER) && (y->type->form == INTEGER)) {
        if ((x->mode == CONST) && (y->mode == CONST)) {
            if (op == terminalSymbols.PLUS.type) {
                x->a += y->a;
            } else if (op == terminalSymbols.MINUS.type) {
                x->a -= y->a;
            } else if (op == terminalSymbols.TIMES.type) {
                x->a *= y->a;
            } else if (op == terminalSymbols.DIV.type) {
                x->a /= y->a;
            } else if (op == terminalSymbols.MOD.type) {
                x->a %= y->a;
            }
        } else {
            if (op == terminalSymbols.PLUS.type) {
                PutOp(ADD, x, y);
            } else if (op == terminalSymbols.MINUS.type) {
                PutOp(SUB, x, y);
            } else if (op == terminalSymbols.TIMES.type) {
                PutOp(MUL, x, y);
            } else if (op == terminalSymbols.DIV.type) {
                PutOp(DIVIDE, x, y);
            } else if (op == terminalSymbols.MOD.type) {
                PutOp(MODULUS, x, y);
            } else
                Mark("�������� ���");
        }
    } else if (x->type->form == BOOLEAN && y->type->form == BOOLEAN) {
        if (y->mode != COND)
            loadBool(y);
        if (op == terminalSymbols.OR.type) {
            x->a = y->a;
            x->b = merged(y->b, x->b);
            x->c = y->c;
        }
    } else Mark("Type mismatch");

}

void Relation(int op, struct Item *x, struct Item *y) {
    if (x->type->form != INTEGER || y->type->form != INTEGER) {
        Mark("Wrong type");

    } else {
        PutOp(CMP, x, y);
        x->c = op - terminalSymbols.EQL.type;
        set_EXCL(regs, y->r);
    }
    x->mode = COND;
    x->type = &boolType;
    x->a = 0;
    x->b = 0;

}

void Store(struct Item *x, struct Item *y) {
    long r;
    if (((x->type->form == BOOLEAN) || (x->type->form == INTEGER)) && (x->type->form == y->type->form)) {
        if (y->mode == COND) {
            Put(BEQ + negated(y->c), y->r, 0, y->a);
            set_EXCL(regs, y->r);
            y->a = pc - 1;
            FixLink(y->b);
            y->r = GetReg();
            Put(MOVI, y->r, 0, 1);
            PutBR(BR, 2);
            FixLink(y->a);
            Put(MOVI, y->r, 0, 0);
        } else if (y->mode != REG)
            load(y);
        if (x->mode == VARIABLE) {
            if (x->level == 0)
                x->a = x->a - pc * 4;
            Put(STW, y->r, x->r, x->a);

        } else
            Mark("Wrong assertion");
        set_EXCL(regs, x->r);
        set_EXCL(regs, y->r);
    } else
        Mark("Type mismatch");
}

void Parameter(struct Item *x, Type *ftyp, int class) {
    long r;
    if (x->type == ftyp) {
        if (class == PAR) {
            if (x->mode == VARIABLE)
                if (x->a != 0) {
                    r = GetReg();
                    if (x->level == 0) {
                        (x->a -= pc * 4);
                    }
                    Put(ADDI, r, x->r, x->a);
                } else
                    r = x->r;
            else
                Mark("Parameter type mismatch");
            Put(PSH, r, SP, 4);
            set_EXCL(regs, r);

        } else {
            if (x->mode != REG)
                load(x);
            Put(PSH, x->r, SP, 4);
            set_EXCL(regs, x->r);
        }
    } else Mark("Parameter type mismatch");

}

void CJump(struct Item *x) {
    if (x->type->form == BOOLEAN) {
        if (x->mode != COND)
            loadBool(x);
        PutBR(BEQ + negated(x->c), x->a);
        set_EXCL(regs, x->r);
        FixLink(x->b);
        x->a = pc - 1;
    } else {
        printf("Boolean?");
        x->a = pc;
    }
}

void BJump(long L) {
    PutBR(BR, L - pc);
}

void FJump(long *L) {
    PutBR(BR, L);
    *L = pc - 1;
}

void Call(struct Item *x) {
    PutBR(BSR, x->a - pc);
}

void IOCall(struct Item *x, struct Item *y) {
    struct Item z;
    if (x->a < 4) {
        if (y->type->form != INTEGER)
            printf("Intege?");

    }
    if (x->a == 1) {
        z.r = GetReg();
        z.mode = REG;
        z.type = &intType;
        Put(RD, z.r, 0, 0);
        Store(y, &z);
    } else if (x->a == 2) {
        load(y);
        Put(WRD, 0, 0, y->r);
        set_EXCL(regs, y->r);
    } else if (x->a == 3) {
        load(y);
        Put(WRH, 0, 0, y->r);
        set_EXCL(regs, y->r);
    } else {
        Put(WRL, 0, 0, 0);
    }

}

void Header(long size) {
    entry = pc;
    Put(MOVI, SP, 0, MemSize - size);
    Put(PSH, LNK, SP, 4);

}

void Enter(long size) {
    Put(PSH, LNK, SP, 4);
    Put(PSH, FP, SP, 4);
    Put(MOV, FP, 0, SP);
    Put(SUBI, SP, SP, size);
}

void Return(long size) {
    Put(MOV, SP, 0, FP);
    Put(POP, FP, SP, 4);
    Put(POP, LNK, SP, size + 4);
    PutBR(RET, LNK);
}

void Open() {
    curlev = 0;
    pc = 0;
    cno = 0;
    regs = set_new();
}


//TODO почему то не используется
void Close(long globals) {
    Put(POP, LNK, SP, 4);
    PutBR(RET, LNK);

}

//Собирает Item comname[ ] и long comaddr[ ]
void EnterCMD(char name[], int nameLength) {
    comname[cno] = ident_new(name, nameLength);
    comaddr[cno] = pc * 4;
    cno++;
}

void decode(char address[]) {

    cg_initialize();

    unsigned long w, op;
    long a;
    char str[150];
    FILE *file = fopen(address, "w+");
    fprintf(file, "Enter:");
    sprintf(str, "%ld", entry * 4);
    fprintf(file, str);
    fprintf(file, "\n");
    for (unsigned long j = 0; j < pc; ++j) {
        w = code[j];
        op = (w >> 26) & 0x3F;
        fprintf(file, "%#.8x %#.8x %-4s ", (unsigned int) j * 4, (unsigned int) w, mnemo[op]);

        if (op < MOVI) {
            fprintf(file, "R%.2lu, R%.2lu, R%.2lu\n", ((w >> 22) & 0x0F), ((w >> 18) & 0x0F), w & 0x0F);
        } else if (op < BEQ) {
            a = (int) (w & 0x3FFFF);
            if (a >= 0x20000) {
                a -= 0x40000;
            }
            fprintf(file, "R%.2lu, R%.2lu, %#+.8x\n", ASH(w, 22) & 0x0F, (w >> 18) & 0x0F, (unsigned int) a);
        } else {
            a = (int) (w & 0x3FFFFFF);

            if (op == RET) {
                // c = link register
                fprintf(file, "R%.2d\n", (int) a);
            } else {
                if (a >= 0x2000000) {
                    a -= 0x4000000;
                }
                fprintf(file, "%#+.6x\n", (unsigned int) a * 4);
            }
        }
    }
    fprintf(file, "\n%d bytes\n", pc * 4);

    fclose(file);

}


void Load(char outputAddress[]) {
    RiscLoad((const long *) code, pc);
    RiscExecute(entry * 4, outputAddress);

}


void Exec(char outputAddress[]) {
    char *s = calloc(20, sizeof(char));
    scanf("%s", s);
    int i = 0;
    while (i < cno && namesEquals(s, sizeof(s), comname[i]->name, comname[i]->nameLength))
        i++;
    if (i < cno)
        RiscExecute(comaddr[i], outputAddress);

}





