CC=gcc
CFLAGS=-c -std=c11 -pedantic -Wall -Wextra

compiler.exe: main.o LexAnalyzer.o SyntaxAnalyzer.o CodeGenerator.o RISC.o Node.o Set.o TerminalSymbols.o Tokens.o SimpleFunctions.o LongList.o
	$(CC) main.o LexAnalyzer.o SyntaxAnalyzer.o CodeGenerator.o RISC.o Node.o Set.o TerminalSymbols.o Tokens.o SimpleFunctions.o LongList.o -o compiler.exe

main.o: main.c
	$(CC) $(CFLAGS) main.c
	
LexAnalyzer.o: Modules/LexAnalyzer.c
	$(CC) $(CFLAGS) Modules/LexAnalyzer.c

SyntaxAnalyzer.o: Modules/SyntaxAnalyzer.c
	$(CC) $(CFLAGS) Modules/SyntaxAnalyzer.c
	
CodeGenerator.o: Modules/CodeGenerator.c
	$(CC) $(CFLAGS) Modules/CodeGenerator.c
	
RISC.o : Modules/RISC.c
	$(CC) $(CFLAGS) Modules/RISC.c
	
Node.o: Modules/Structures/Node.c
	$(CC) $(CFLAGS) Modules/Structures/Node.c
	
Set.o: Modules/Structures/Set.c
	$(CC) $(CFLAGS) Modules/Structures/Set.c

TerminalSymbols.o: Modules/Structures/TerminalSymbols.c
	$(CC) $(CFLAGS) Modules/Structures/TerminalSymbols.c
	
Tokens.o: Modules/Structures/Tokens.c
	$(CC) $(CFLAGS) Modules/Structures/Tokens.c
	
SimpleFunctions.o: Modules/SimpleFunctions/SimpleFunctions.c
	$(CC) $(CFLAGS) Modules/SimpleFunctions/SimpleFunctions.c

LongList.o: Modules/Structures/LongList.c
	$(CC) $(CFLAGS) Modules/Structures/LongList.c
