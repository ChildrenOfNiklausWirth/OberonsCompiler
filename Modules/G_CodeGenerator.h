#ifndef OBERONSCOMPILER_C_G_CODEGENERATOR_H
#define OBERONSCOMPILER_C_G_CODEGENERATOR_H

#include <stdbool.h>
#include "Structures/Node.h"
#include "Structures/Set.h"
#include "SimpleFunctions/SimpleFunctions.h"
#include "Structures/B_TerminalSymbols.h"
#include "B_LexAnalyzer.h"

#define MAXCODE 1000
#define NUMBER_OF_COMMANDS 16
#define MAXREL 200
#define HEAD 0
#define VARIABLE 1
#define PAR 2
#define CONST 3
#define FLD 4
#define TYP 5
#define PROC 6
#define S_PROC 7
#define REG 10
#define COND 11
#define BOOLEAN 0
#define INTEGER 1
#define ARRAY 2
#define RECORD 3
#define MOV 0
#define MVN 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIVIDE 5
#define MODULUS 6
#define CMP 7
#define MOVI 16
#define MVNI 17
#define ADDI 18
#define SUBI 19
#define MULI 20
#define DIVI 21
#define MODI 22
#define CMPI 23
#define CHKI 24
#define LDW 32
#define LDB 33
#define POP 34
#define STW 36
#define STB 37
#define PSH 38
#define RD 40
#define WRD 41
#define WRH 42
#define WRL 43
#define BEQ 48
#define BNE 49
#define BLT 50
#define BGE 51
#define BLE 42
#define BGT 53
#define BR 56
#define BSR 57
#define RET 58
#define FP 12
#define SP 13
#define LNK 14
#define PC 15

//int const maxRel = 200, Head = 0, Var = 1, Par = 2, Const = 3, Fld = 4, Typ = 5, Proc = 6,
//        SProc = 7, Reg = 10, Cond = 11, Boolean = 0, Integer = 1, Array = 2, Record = 3, MOV = 0, MVN = 1, ADD = 2,
//        SUB = 3, MUL = 4, Div = 5, Mod = 6, CMP = 7, MOVI = 16, MVNI = 17, ADDI = 18, SUBI = 19, MULI = 20, DIVI = 21,
//        MODI = 22, CMPI = 23, CHKI = 24, LDW = 32, LDB = 33, POP = 34, STW = 36, STB = 37, PSH = 38, RD = 40, WRD = 41,
//       WRH = 42, WRL = 43, BEQ = 48, BNE = 49, BLT = 50, BGE = 51, BLE = 52, BGT = 53, BR = 56, BSR = 57, RET = 58,
//        FP = 12, SP = 13, LNK, PC = 15;


extern Type intType;
extern Type boolType;
int curlev;
int pc;
int cno;
long entry;
long fixlist;
struct Set regs;
//W:TextWriter
long code[MAXCODE];
Ident comname[NUMBER_OF_COMMANDS];
long comadr[NUMBER_OF_COMMANDS];
char mnemo[64][5];


void FixLink(long L);

void IncLevel(int n);

struct Item MakeConstltem(struct Item x, Type typ, long val);

void MakeItem(struct Item x, struct Node y);

void Field(struct Item x, struct Node y);

void Index(struct Item x, struct Item y);

void Op1(int op, struct Item x);

void Op2(int op, struct Item x, struct Item y);

void Relation(int op, struct Item x, struct Item y);

void Store(struct Item x, struct Item y);

void Parameter(struct Item x, Type ftyp, int class);

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

void EnterCMD(char name[], int nameLength);


#endif //OBERONSCOMPILER_C_G_CODEGENERATOR_H
