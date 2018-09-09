#ifndef OBERONSCOMPILER_C_G_CODEGENERATOR_H
#define OBERONSCOMPILER_C_G_CODEGENERATOR_H

#include "Structures/Node.h"
#include "Structures/LongList.h"
#include <stdbool.h>
#include <stdio.h>

#define MAXCODE 10000
#define NUMBER_OF_COMMANDS 16
#define MAXREL 200

////Constants for Node.class and Item.mode
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

//Constants for
#define BOOLEAN 0
#define INTEGER 1
#define ARRAY 2
#define RECORD 3

//Constants for assembler
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
#define BLE 52
#define BGT 53
#define BR 56
#define BSR 57
#define RET 58
#define FP 12
#define SP 13
#define LNK 14
#define PC 15


extern Type intType;
extern Type boolType;
int curlev;
int pc;
int cno;
long entry;
long fixlist;
struct Set *regs;
//W:TextWriter
//long code[MAXCODE];
//comname
//char mnemo[64][5];

void cg_initialize();

unsigned long encode(long op, long a, long b, long c);

unsigned long encodeF3(long op, long disp);

void decodeHex(FILE *outputFile);

void laconicDecode(FILE *outputFile);

void FixLink(long L);

void IncLevel(int n);

void MakeConstltem(struct Item *item, Type *typ, long val);

void MakeItem(struct Item *item, Node *node);

void Field(struct Item *item, Node *node);

void Index(struct Item *item1, struct Item *item2);

void Op1(int op, struct Item *item);

void Op2(int op, struct Item *item1, struct Item *item2);

void Relation(int op, struct Item *item1, struct Item *item2);

void Store(struct Item *item1, struct Item *item2);

void Parameter(struct Item *item, Type *ftyp, int class);

void CJump(struct Item *item);

void BJump(long L);

void FJump(long *L);

void Call(struct Item *item);

void IOCall(struct Item *item1, struct Item *item2);

void Header(long size);

void Enter(long size);

void Return(long size);

void Open();

void Close(long globals);

void EnterCMD(char *name, int nameLength);

LongList Load(FILE *loadFile);

void Exec(FILE *outputFile);

#endif //OBERONSCOMPILER_C_G_CODEGENERATOR_H
