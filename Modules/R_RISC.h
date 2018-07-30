#ifndef OBERONSCOMPILER_C_R_RISC_H
#define OBERONSCOMPILER_C_R_RISC_H

#include <stdbool.h>
#include <stdio.h>
#include "SimpleFunctions/SimpleFunctions.h"

#define MemSize 4096
#define ProgOrg 2048
#define MOV 0
#define MVN 1
#define ADD 2
#define SUB 3
#define MUL 4
#define Div 5
#define Mod 6
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


long IR;
bool N, Z;
long R[16];
long M[MemSize / 4];
FILE W;

void Execute(long start, char inputAddres[], char outputAddress[]);

#endif //OBERONSCOMPILER_C_R_RISC_H
