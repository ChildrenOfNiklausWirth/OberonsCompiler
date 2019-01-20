NAME = oberon_compiler

CC = gcc

CFLAGS = -g -O0 -std=c11 -pedantic -Wall -Wextra

SOURCES =   Modules/LexAnalyzer.c Modules/SyntaxAnalyzer.c \
			Modules/CodeGenerator.c Modules/RISC.c Modules/Structures/Node.c \
			Modules/Structures/Set.c Modules/Structures/TerminalSymbols.c \
			Modules/Structures/Tokens.c \
			Modules/SimpleFunctions/SimpleFunctions.c Modules/Structures/LongList.c \
			Tests/TestsForModules/T_B_LexAnalyzer.c \
			Tests/TestsForModules/T_Z_CodeGenerationAndExecuting.c 
			


all: 
	$(CC) $(CFLAGS) -o $(NAME) main.c $(SOURCES) 

clean: 
	rm $(NAME)
	
remake: clean all 
	