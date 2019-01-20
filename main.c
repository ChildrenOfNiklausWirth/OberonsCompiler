#include <stdlib.h>
#include "Modules/LexAnalyzer.h"
#include "Modules/CodeGenerator.h"
#include "Modules/SyntaxAnalyzer.h"
#include "Tests/TestsForModules/T_B_LexAnalyzer.h"
#include "Tests/TestsForModules/T_Z_CodeGenerationAndExecuting.h"
#include <getopt.h>
#ifdef _WIN32
#include <mem.h>
#elif __linux
#include <string.h>
#endif


int main(int argc, char *argv[]) {

	int FLAG_LOAD = 1;
	int FLAG_EXECUTABLE = 0;
	int EXECUTE_MODE = 0;


	char inputFileName[1024];
	//char *decodedFileName;
	char decodedFileNameHex[1024];
	int opt_index = 1;

	int opt;
	while ((opt = getopt(argc, argv, "w:e:t")) != -1) //XXX changed
	{
		switch (opt) {
		/* Run tests*/
		case 't':
			lex_tests();
			code_generation_and_executing_tests();
			opt_index++;
			break;
			/* Execute file*/
		case 'e':
			EXECUTE_MODE = 1;
			strcpy(inputFileName, optarg);
			opt_index++;
			break;

			/*Write risc code to file*/
		case 'w':
			strcpy(decodedFileNameHex, optarg);
			opt_index++;
			break;

		default:
			fprintf(stderr, "Undefined option %s\n", argv[opt_index]);
			exit(1);
		}
	}
	if (EXECUTE_MODE) {
		FILE *inputFile = fopen(inputFileName, "r");
		//FILE *decodedFile = fopen(decodedFileName, "w+");
		FILE *decodedFileHex = fopen(decodedFileNameHex, "w+");
		FILE *outputFile = stdout;

		if (inputFile != NULL) {
			lexAnalysis(inputFile, outputFile);
			module();
			decodeHex(decodedFileHex);
			//laconicDecode(decodedFile);

			if (FLAG_EXECUTABLE && (syntaxError == 0))
				Exec(outputFile);
			if (FLAG_LOAD && (syntaxError == 0))
				Load(outputFile);
			return 0;
		} else {
			printf("No such file \"%s\"", inputFileName);
		}
	}

	exit(0);
}

