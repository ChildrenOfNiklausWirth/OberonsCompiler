#include "G_CodeGenerator.h"


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
        OSS.Mark("Значение слишком большое");//TODO

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

void Index(struct Item x, struct Item y) {
    if (type_equals(y.type, intType) == 0)
        OSS.Mark("индекс не целое");
    if (y.mode == Const) {
        if ((y.a < 0) || (y.a >= x.type.len))
            OSS.Mark("неверный индекс");
    } else {
        if (y.mode != Reg)
            load(y);
        Put(CHKI, y.r, 0, x.type.len);
        Put(MULI, y.r, y.r, x.type.base.size);
        Put(ADD, y.r, x.r, y.r);
        set_EXCL(&regs, x.r);
        x.r = y.r;
    }
    x.type = x.type.base;
}

void Op1(int op, struct Item x) {
    long t;
    if (op == OSS.minus)
        if (x.type.form != Integer) {
            OSS.Mark("неверный тип");
        } else if (x.mode == Const) {
            x.a = -x.a;
        } else {
            if (x.mode == Var)
                load(x);
            Put(MVN, x.r, 0, x.r);
        }
    else if (op == OSS.not) {
        if (x.mode != Cond) {
            loadBool(x);
        }
        x.c = negated(x.c);
        t = x.a;
        x.a = x.b;
        x.b = t;
    } else if (op == OSS.and) {
        if (x.mode != Cond)
            loadBool(x);
        PutBR(BEQ + negated(x.c), x.a);
        set_EXCL(&regs, x.r);
        x.a = pc - 1;
        FixLink(x.b);
        x.b = 0;
    } else if (op == OSS.or) {
        if (x.mode != Cond)
            loadBool(x);
        PutBR(BEQ + x.c, x.b);
        set_EXCL(&regs, x.r);
        x.b = pc - 1;
        FixLink(x.a);
        x.a = 0;
    }
}

void Op2(int op, struct Item x, struct Item y) {
    if (x.type.form == Integer && y.type.form == Integer) {
        if (x.mode == Const && y.mode == Const) {
            if (op == terminalSymbols.PLUS.type) {
                x.a += y.a;
            } else if (op == terminalSymbols.MINUS.type) {
                x.a -= y.a;
            } else if (op == terminalSymbols.TIMES.type) {
                x.a *= y.a;
            } else if (op == terminalSymbols.DIV.type) {
                x.a /= y.a;
            } else if (op == terminalSymbols.MOD.type) {
                x.a %= y.a;
            }
        } else {
            if (op == terminalSymbols.PLUS.type) {
                PutOp(ADD, x, y);
            } else if (op == terminalSymbols.MINUS.type) {
                PutOp(SUB, x, y);
            } else if (op == terminalSymbols.TIMES.type) {
                PutOp(MUL, x, y);
            } else if (op == terminalSymbols.DIV.type) {
                PutOp(Div, x, y);
            } else if (op == terminalSymbols.MOD.type) {
                PutOp(Mod, x, y);
            } else
                OSS.Mark("неверный тип");
        }
    } else if (x.type.form == Boolean && y.type.form == Boolean) {
        if (y.mode != Cond)
            loadBool(y);
        if (op == terminalSymbols.OR.type) {
            x.a = y.a;
            x.b = merged(y.b, x.b);
            x.c = y.c;
        }
    } else OSS.Mark("неверный тип");
}

void Relation(int op, struct Item x, struct Item y) {
    if (x.type.form != Integer || y.type.form != Integer) {
        OSS.Mark("неверный тип");

    } else {
        PutOp(CMP, x, y);
        x.c = op - terminalSymbols.EQL.type;
        set_EXCL(&regs, y.r);
    }
    x.mode = Cond;
    x.type = boolType;
    x.a = 0;
    x.b = 0;
}

void Store(struct Item x, struct Item y) {
    long r;
    if ((x.type.form == Boolean || x.type.form == Integer) && (x.type.form == y.type.form)) {
        if (y.mode == Cond) {
            Put(BEQ + negated(y.c), y.r, 0, y.a);
            set_EXCL(&regs, y.r);
            y.a = pc - 1;
            FixLink(y.b);
            GetReg(y.r);
            Put(MOVI, y.r, 0, 1);
            PutBR(BR, 2);
            FixLink(y.a);
            Put(MOVI, y.r, 0, 0);
            //127
        } else if (y.mode != Reg)
            load(y);
        if (x.mode == Var) {
            if (x.level == 0)
                x.a = x.a - pc * 4;
            Put(STW, y.r, x.r, x.a);

        } else
            OSS.Mark("неправильное присваивание");
        set_EXCL(&regs, x.r);
        set_EXCL(&regs, y.r);
    } else
        OSS.Mark("невсоместимое присваивание");


}

void Parameter(struct Item x, struct Type ftyp, int class) {
    long r;
    if (type_equals(x.type, ftyp) == 1) {
        if (class == Par) {
            if (x.mode == Var)
                if (x.a != 0) {
                    GetReg(r);
                    Put(ADDI, r, x.r, x.a);
                } else
                    r = x.r;
            else
                OSS.Mark("неправильный режим параметра");
            Put(PSH, r, SP, 4);
            set_EXCL(&regs, r);

        } else {
            if (x.mode != Reg)
                load(x);
            Put(PSH, x.r, SP, 4);
            set_EXCL(&regs, x.r);
        }
    } else OSS.Mark("неверный тип параметра");

}

void CJump(struct Item x) {
    if (x.type.form == Boolean) {
        if (x.mode != Cond)
            loadBool(x);
        PutBR(BEQ + negated(x.c), x.a);
        set_EXCL(&regs, x.r);
        FixLink(x.b);
        x.a = pc - 1;
    } else {
        printf("Boolean?");
        x.a = pc;
    }
}


void BJump(long L) {
    PutBR(BR, L - pc);
}

void FJump(long L) {
    PutBR(BR, L);
    L = pc = 1;
}

void Call(struct Item x) {
    PutBR(BSR, x.a - pc);
}

void IOCall(struct Item x, struct Item y) {
    struct Item z;
    if (x.a < 4) {
        if (y.type.form != Integer)
            printf("Intege?");

    }
    if (x.a == 1) {
        GetReg(z.r);
        z.mode = Reg;
        z.type = intType;
        Put(RD, z.r, 0, 0);
        Store(y, z);
    } else if (x.a == 2) {
        load(y);
        Put(WRD, 0, 0, y.r);
        set_EXCL(&regs, y.r);
    } else if (x.a == 3) {
        load(y);
        Put(WRH, 0, 0, y.r);
        set_EXCL(&regs, y.r);
    } else {
        Put(WRL, 0, 0, 0);
    }

}

void Header(long size) {
    entry = pc;
    Put(MOVI, SP, 0, RISC.MemSize - size);
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
    regs = set_newSet();
}

void Close(long globals) {
    Put(POP, LNK, SP, 4);
    PutBR(RET, LNK);

}

//TODO
//void EnterCMD(char name[]){
//}

