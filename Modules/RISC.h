#ifndef OBERONSCOMPILER_C_R_RISC_H
#define OBERONSCOMPILER_C_R_RISC_H
#include "Structures/LongList.h"
#include <stdbool.h>
#include <stdio.h>


#define RMemSize 1024
#define ProgOrg 0

//F0
#define MOV 0
#define MVN 1
#define ADD 2
#define SUB 3
#define MUL 4
#define Div 5
#define Mod 6
#define CMP 7

//F1
#define MOVI 16
#define MVNI 17
#define ADDI 18
#define SUBI 19
#define MULI 20
#define DIVI 21
#define MODI 22
#define CMPI 23
#define CHKI 24

//F2
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

//F3
#define BEQ 48
#define BNE 49
#define BLT 50
#define BGE 51
#define BLE 52
#define BGT 53
#define BR 56
#define BSR 57
#define RET 58


void myDecode(unsigned int IR, unsigned int *opc, int *a, int *b, int *c);

void wirthDecode(unsigned int IR, int *opc, int *a, int *b, int *c);

void RiscExecute(int start, FILE *outputFile);

void RiscLoad(const long code[], long len);


#endif //OBERONSCOMPILER_C_R_RISC_H
