#include "G_CodeGenerator.h"

int MemSize = 1024;
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
unsigned long encode(long op, long a, long b, long c) {
    if (op >= 32)
        op -= 64;
    return  ((((((op << 4) | a) << 4) | b) << 18) | ((unsigned long) c & 0x3FFFF));
}

void Put(long op, long a, long b, long c) {
    code[pc] = encode(op, a, b, c);
    pc++;
}

//Генерирует команды формата F3 (команды перехода)
unsigned long encodeF3(long op, long disp) {
    return (unsigned long) ((op - (1 << 6)) << 26) | (disp & 0x3FFFFFF);
}

void PutBR(long op, long disp) {
    code[pc] = (unsigned long) (op - 0x40) << 26 | (disp & 0x3FFFFFF);
    pc++;
}

//Проверяет размер переменной
void TestRange(long x) {
    if ((x >= (1 << 17)) || (x < -(1 << 17)))
        Mark("Value is out of range", -1);

}

//Загружает переменную или константу в code[ ]
struct Item load(struct Item *item) {
    long r;
    if (item->mode == VARIABLE) {
        if (item->level == 0)
            item->a = MemSize + item->a - pc * 4;
        r = GetReg();
        Put(LDW, r, item->r, item->a);
        set_EXCL(regs, item->r);
        item->r = r;
    } else if (item->mode == CONST) {
        TestRange(item->a);
        item->r = GetReg();
        Put(MOVI, item->r, 0, item->a);
    }
    item->mode = REG;
}

struct Item loadBool(struct Item *item) {
    if (item->type->form != BOOLEAN)
        Mark("Boolean?", -1);
    load(item);
    item->mode = COND;
    item->a = 0;
    item->b = 0;
    item->c = 1;
}

//Генерирует операцию с двумя операндами
void PutOp(long operation, struct Item *item1, struct Item *item2) {
    if (item1->mode != REG)
        load(item1);
    if (item2->mode == CONST) {
        TestRange(item2->a);
        Put(operation + 16, item1->r, item1->r, item2->a);
    } else {
        if (item2->mode != REG)
            load(item2);
        Put(operation, item1->r, item1->r, item2->r);
        set_EXCL(regs, item2->r);
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
            L3 = code[L2] % (1 << 18);
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
    code[at] = (code[at] & 0xFFC00000) | (with & 0x3FFFFF);
}

long fixWith(long L0, long L1) {
    long L2;
    while (L0 != 0) {
        L2 = code[L0] % (1 << 18);
        fix(L0, L1 - L0);
        L0 = L2;
    }
    return L0;

}

long FixLink(long L) {
    long L1;
    while (L != 0) {
        L1 = code[L] & 0x3FFFF;
        fix(L, pc - L);
        L = L1;
    }
}

void IncLevel(int n) {
    curlev += n;
}

void MakeConstltem(struct Item *item, Type *typ, long val) {
    item->mode = CONST;
    item->type = typ;
    item->a = val;
}

//Создает Item на основе Node
void MakeItem(struct Item *item, Node *node) {
    long r;

    item->mode = node->class;
    item->type = node->type;
    item->level = node->level;
    item->a = node->val;
    item->b = 0;

    if (node->level == 0) {
        item->r = PC;
    } else if (node->level == curlev)
        item->r = FP;
    else {
        Mark("Level mismatch!", -1);
        item->r = 0;
    }
    if (node->class == PAR) {
        r = GetReg();
        Put(LDW, r, item->r, item->a);
        item->mode = VARIABLE;
        item->r = r;
        item->a = 0;
    }
}

void Field(struct Item *item, Node *node) {
    item->a += node->val;
    item->type = node->type;
}

void Index(struct Item *item1, struct Item *item2) {
    if (item2->type != &intType)
        Mark("Index isn't integer", -1);
    if (item2->mode == CONST) {
        if ((item2->a < 0) || (item2->a >= item1->type->len))
            Mark("Wrong index", -1);
    } else {
        if (item2->mode != REG)
            load(item2);
        Put(CHKI, item2->r, 0, item1->type->len);
        Put(MULI, item2->r, item2->r, item1->type->base->size);
        Put(ADD, item2->r, item1->r, item2->r);
        set_EXCL(regs, item1->r);
        item1->r = item2->r;
    }
    item1->type = item1->type->base;
}

void Op1(int op, struct Item *item) {
    long t;
    if (op == terminalSymbols.MINUS.type)
        if (item->type->form != INTEGER) {
            Mark("Type mismatch", -1);
        } else if (item->mode == CONST) {
            item->a = -item->a;
        } else {
            if (item->mode == VARIABLE)
                load(item);
            Put(MVN, item->r, 0, item->r);
        }
    else if (op == terminalSymbols.NOT.type) {
        if (item->mode != COND) {
            loadBool(item);
        }
        item->c = negated(item->c);
        t = item->a;
        item->a = item->b;
        item->b = t;
    } else if (op == terminalSymbols.AND.type) {
        if (item->mode != COND)
            loadBool(item);
        PutBR(BEQ + negated(item->c), item->a);
        set_EXCL(regs, item->r);
        item->a = pc - 1;
        FixLink(item->b);
        item->b = 0;
    } else if (op == terminalSymbols.OR.type) {
        if (item->mode != COND)
            loadBool(item);
        PutBR(BEQ + item->c, item->b);
        set_EXCL(regs, item->r);
        item->b = pc - 1;
        FixLink(item->a);
        item->a = 0;
    }

}

//Генерирует выражения вида item1.a op item2.b
void Op2(int op, struct Item *item1, struct Item *item2) {
    if ((item1->type->form == INTEGER) && (item2->type->form == INTEGER)) {
        if ((item1->mode == CONST) && (item2->mode == CONST)) {
            if (op == terminalSymbols.PLUS.type) {
                item1->a += item2->a;
            } else if (op == terminalSymbols.MINUS.type) {
                item1->a -= item2->a;
            } else if (op == terminalSymbols.TIMES.type) {
                item1->a *= item2->a;
            } else if (op == terminalSymbols.DIV.type) {
                item1->a /= item2->a;
            } else if (op == terminalSymbols.MOD.type) {
                item1->a %= item2->a;
            }
        } else {
            if (op == terminalSymbols.PLUS.type) {
                PutOp(ADD, item1, item2);
            } else if (op == terminalSymbols.MINUS.type) {
                PutOp(SUB, item1, item2);
            } else if (op == terminalSymbols.TIMES.type) {
                PutOp(MUL, item1, item2);
            } else if (op == terminalSymbols.DIV.type) {
                PutOp(DIVIDE, item1, item2);
            } else if (op == terminalSymbols.MOD.type) {
                PutOp(MODULUS, item1, item2);
            } else
                Mark("�������� ���", -1);
        }
    } else if (item1->type->form == BOOLEAN && item2->type->form == BOOLEAN) {
        if (item2->mode != COND)
            loadBool(item2);
        if (op == terminalSymbols.OR.type) {
            item1->a = item2->a;
            item1->b = merged(item2->b, item1->b);
            item1->c = item2->c;
        } else if (op == terminalSymbols.AND.type) {
            item1->a = merged(item2->a, item1->a);
            item1->b = item2->b;
            item1->c = item2->c;
        }
    } else Mark("Type mismatch", -1);

}

void Relation(int op, struct Item *item1, struct Item *item2) {
    if (item1->type->form != INTEGER || item2->type->form != INTEGER) {
        Mark("Wrong type", -1);

    } else {
        PutOp(CMP, item1, item2);
        item1->c = op - terminalSymbols.EQL.type;
        set_EXCL(regs, item2->r);
    }
    item1->mode = COND;
    item1->type = &boolType;
    item1->a = 0;
    item1->b = 0;

}

void Store(struct Item *item1, struct Item *item2) {
    long r;
    if (((item1->type->form == BOOLEAN) || (item1->type->form == INTEGER)) &&
        (item1->type->form == item2->type->form)) {
        if (item2->mode == COND) {
            Put(BEQ + negated(item2->c), item2->r, 0, item2->a);
            set_EXCL(regs, item2->r);
            item2->a = pc - 1;
            FixLink(item2->b);
            item2->r = GetReg();
            Put(MOVI, item2->r, 0, 1);
            PutBR(BR, 2);
            FixLink(item2->a);
            Put(MOVI, item2->r, 0, 0);
        } else if (item2->mode != REG)
            load(item2);
        if (item1->mode == VARIABLE) {
            if (item1->level == 0)
                item1->a = (MemSize + item1->a) - pc * 4;
            Put(STW, item2->r, item1->r, item1->a);

        } else
            Mark("Wrong assertion", -1);
        set_EXCL(regs, item1->r);
        set_EXCL(regs, item2->r);
    } else
        Mark("Type mismatch", -1);
}

void Parameter(struct Item *item, Type *ftyp, int class) {
    long r;
    if (item->type == ftyp) {
        if (class == PAR) {
            if (item->mode == VARIABLE)
                if (item->a != 0) {
                    r = GetReg();
                    if (item->level == 0) {
                        (item->a = MemSize + item->a - pc * 4);
                    }
                    Put(ADDI, r, item->r, item->a);
                } else
                    r = item->r;
            else
                Mark("Parameter type mismatch", -1);
            Put(PSH, r, SP, 4);
            set_EXCL(regs, r);

        } else {
            if (item->mode != REG)
                load(item);
            Put(PSH, item->r, SP, 4);
            set_EXCL(regs, item->r);
        }
    } else Mark("Parameter type mismatch", -1);

}

void CJump(struct Item *item) {
    if (item->type->form == BOOLEAN) {
        if (item->mode != COND)
            loadBool(item);
        PutBR(BEQ + negated(item->c), item->a);
        set_EXCL(regs, item->r);
        FixLink(item->b);
        item->a = pc - 1;
    } else {
        printf("Boolean?");
        item->a = pc;
    }
}

//Генерация команды перехода BR
void BJump(long L) {
    PutBR(BR, L - pc);
}

//Генерация команды перехода BR
void FJump(long *L) {
    PutBR(BR, *L);
    *L = pc - 1;
}

//Генерация команды BSR по item->a
void Call(struct Item *item) {
    PutBR(BSR, item->a - pc);
}

void IOCall(struct Item *item1, struct Item *item2) {
    struct Item z;

    if (item1->a < 4) {
        if (item2->type->form != INTEGER)
            printf("Integer?");
    }

    if (item1->a == 1) {
        z.r = GetReg();
        z.mode = REG;
        z.type = &intType;
        Put(RD, z.r, 0, 0);
        Store(item2, &z);
    } else if (item1->a == 2) {
        load(item2);
        Put(WRD, 0, 0, item2->r);
        set_EXCL(regs, item2->r);
    } else if (item1->a == 3) {
        load(item2);
        Put(WRH, 0, 0, item2->r);
        set_EXCL(regs, item2->r);
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

void decode(FILE *outputFile) {

    cg_initialize();

    unsigned long w, op;
    long a;
    char str[150];
    fprintf(outputFile, "Enter: %#+.8x\n", entry * 4);
    for (unsigned long j = 0; j < pc; ++j) {
        w = code[j];
        op = (w >> 26) & 0x3F;
        fprintf(outputFile, "%#.8x %#.8x %-4s ", (unsigned int) j * 4, (unsigned int) w, mnemo[op]);

        if (op < MOVI) {
            fprintf(outputFile, "R%.2lu, R%.2lu, R%.2lu\n", ((w >> 22) & 0x0F), ((w >> 18) & 0x0F), w & 0x0F);
        } else if (op < BEQ) {
            a = (int) (w & 0x3FFFF);
            if (a >= 0x20000) {
                a -= 0x40000;
            }
            fprintf(outputFile, "R%.2lu, R%.2lu, %s%#+.8x\n", w >> 22 & 0x0F, w >> 18 & 0x0F, a < 0?"-":"", a < 0 ? - (unsigned) a : (unsigned) a);
        } else {
            a = (int) (w & 0x3FFFFFF);

            if (op == RET) {
                // c = link register
                fprintf(outputFile, "R%.2d\n", a);
            } else {
                if (a >= 0x2000000) {
                    a -= 0x4000000;
                }
                fprintf(outputFile, "%s%#+.6x\n", a < 0 ? "-":"", a < 0 ? - (unsigned) (a * 4) : (unsigned) a * 4);
            }
        }
    }
    fprintf(outputFile, "\n%d bytes\n", pc * 4);

    fclose(outputFile);

}


void Load(FILE *outputFile) {
    RiscLoad((const long *) code, pc);
    RiscExecute(entry * 4, outputFile);
}


void Exec(FILE *outputFile) {
    char *s = calloc(20, sizeof(char));
    scanf("%s", s);
    int i = 0;
    while (i < cno && namesEquals(s, sizeof(s), comname[i]->name, comname[i]->nameLength))
        i++;
    if (i < cno)
        RiscExecute(comaddr[i], outputFile);
}





