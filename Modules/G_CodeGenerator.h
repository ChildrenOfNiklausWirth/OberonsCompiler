#ifndef OBERONSCOMPILER_C_G_CODEGENERATOR_H
#define OBERONSCOMPILER_C_G_CODEGENERATOR_H
#include <stdbool.h>
#include "Structures/Object.h"
#include "Structures/Set.h"
#include "SimpleFunctions/SimpleFunctions.h"
#include "Structures/B_TerminalSymbols.h"
#include "B_LexAnalyzer.h"


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


void FixLink(long L);

void IncLevel(int n);

void MakeConstltem(struct Item x, struct Type typ, long val);

void MakeItem(struct Item x, struct Object y);

void Field(struct Item x, struct Object y);

void Index(struct Item x, struct Item y);

void Op1(int op, struct Item x);

void Op2(int op, struct Item x, struct Item y);

void Relation(int op, struct Item x, struct Item y);

void Store(struct Item x, struct Item y);

void Parameter(struct Item x, struct Type ftyp, int class);

void CJump(struct Item x);

void BJump(long L);

void FJump(long L);

void Call(struct Item x);

void IOCall(struct Item x, struct Item y);

void Header(long size);

void Enter(long size);

void Return(long size);

void Open();

void Close(long globals);

#endif //OBERONSCOMPILER_C_G_CODEGENERATOR_H
