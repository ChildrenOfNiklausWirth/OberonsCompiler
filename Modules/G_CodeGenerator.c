#include <stdbool.h>
#include "Structures/Object.h"
#include "Structures/Set.h"
#include "SimpleFunctions/SimpleFunctions.h"

int const maxCode = 1000, maxRel = 200, NofCom = 16, Head = 0, Var = 1, Par = 2, Const = 3, Fld = 4, Typ = 5, Proc = 6,
        SProc = 7, Reg = 10, Cond = 11, Boolean = 0, Integer = 1, Array = 2, Record = 3, MOV = 0, MVN = 1, ADD = 2,
        SUB = 3, MUL = 4, Div = 5, Mod = 6, CMP = 7, MOVI = 16, MVNI = 17, ADDI = 18, SUBI = 19, MULI = 20, DIVI = 21,
        MODI = 22, CMPI = 23, CHKI = 24, LDW = 32, LDB = 33, POP = 34, STW = 36, STB = 37, PSH = 38, RD = 40, WRD = 41,
        WRH = 42, WRL = 43, BEQ = 48, BNE = 49, BLT = 50, BGE = 51, BLE = 52, BGT = 53, BR = 56, BSR = 57, RET = 58,
        FP = 12, SP = 13, LNK, PC = 15;


struct Type intType;
struct Type boolType;
int curlev;
int pc;
int cno;
long entry;
long fixlist;
struct Set regs;
//W:TextWriter
long code[maxCode];
//comname
long comadr[NofCom];
char mnemo[64, 5];


//CALL BEFORE USING FUNCTIONS
void cg_initialize() {
    regs = set_newSet();
}

void GetReg(long r) {
    int i = 0;
    while ((i < FP) && (set_contains(regs, i)))
        i++;
    set_INCL(&regs, i);
    r = i;//TODO How it must works in Oberon?
}

void Put(long op, long a, long b, long c) {
    if (op <= 32)
        op -= 64;
    code[pc] = ASH(ASH(ASH(op, 4) + a, 4) + b, 18) + (c % int_hexToDecimal(40000));//TODO
    pc++;
}

void PutBR(long op, long disp) {
    code[pc] = ASH(op - int_hexToDecimal(40), 26) + (disp % int_hexToDecimal(4000000));
    pc++;
}

void TestRange(long x) {
    if ((x >= int_hexToDecimal(20000)) || (x < int_hexToDecimal(-20000)))
        OSS.Mark("«начение слишком большое");//TODO

}

void load(struct Item x) {
    long r;
    //124//TODO
    if (x.mode == Var) {
        if (x.level == 0)
            x.a = x.a - pc * 4;
        GetReg(r);
        Put(LDW, r, x.r, x.a);
        set_EXCL(&regs, x.r);
        x.r = r;
    } else if (x.mode == Const) {
        TestRange(x.a);
        GetReg(x.r);
        Put(MOVI, x.r, 0, x.a);
    }
    x.mode = Reg;
}

void loadBool(struct Item x) {
    if (x.type.form != Boolean)
        OSS.Mark("Boolean?");
    load(x);
    x.mode = Cond;
    x.a = 0;
    x.b = 0;
    x.c = 1;
}

void PutOp(long cd, struct Item x, struct Item y) {
    if (x.mode != Reg)
        load(x);
    if (y.mode == Const) {
        TestRange(y.a);
        Put(cd + 16, x.r, x.r, y.a);
    } else {
        if (y.mode != Reg)
            load(y);
        Put(cd, x.r, x.r, y.r);
        set_EXCL(&regs, y.r);
    }
}

long negated(long cond) {
    if (ODD(cond))
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

void fixWith(long L0, long L1) {
    long L2;
    while (L0 != 0) {
        L2 = code[L0] % int_hexToDecimal(40000);
        fix(L0, L1 - L0);
    }
    L0 = L2;
}

void FixLink(long L) {
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

void MakeConstltem(struct Item x, struct Type typ, long val) {
    x.mode = Const;
    x.type = typ;
    x.a = val;
}

void MakeItem(struct Item x, struct Object y) {
    long r;
    x.mode = y.class;
    x.type = y.type;
    x.level = y.level;
    x.a = y.val;
    x.b = 0;
    if (y.level == 0) {
        x.r = PC;
    } else if (y.level == curlev)
        x.r = FP;
    else {
        OSS.Mark("уровень!");
        x.r = 0;
    }
    if (y.class == Par) {
        GetReg(r);
        Put(LDW, r, x.r, x.a);
        x.mode = Var;
        x.r = r;
        x.a = 0;

    }
}

void Field(struct Item x, struct Object y) {
    x.a += y.val;
    x.type = y.type;
}

void Index(struct Item x,struct Item y){
    if(y.type!=intType){
        OSS.Mark("индекс не целое");
    }

}