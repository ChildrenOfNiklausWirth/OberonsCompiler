cmake_minimum_required(VERSION 3.9)
project(OberonsCompiler C)

set(CMAKE_C_STANDARD 11)

add_executable(OberonsCompiler main.c Modules/Parser.c Modules/A_Parser.c Modules/B_LeksAnalyzer.c Modules/C_SyntaxAnalyzer.c Modules/D_SemanticAnalyzer.c Modules/G_CodeGenerator.c)