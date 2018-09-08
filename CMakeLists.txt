cmake_minimum_required(VERSION 3.9)
project(OberonsCompiler_C)

set(CMAKE_C_STANDARD 11)

set(LIBRARIES
        Modules/Structures/B_TerminalSymbols.c
        Modules/Structures/A_Tokens.c
        Modules/B_LexAnalyzer.c
        Modules/C_SyntaxAnalyzer.c
        Modules/G_CodeGenerator.c
        Modules/SimpleFunctions/SimpleFunctions.c
        Modules/Structures/Node.c
        Modules/Structures/Set.c
        Modules/R_RISC.c
        )


add_library(lib STATIC ${LIBRARIES})

set(TEST test.c)
set(MAIN main.c)
set(TEST_TOKENS Tests/TestsForStructures/T_Tokens.c)
set(TEST_SET Tests/TestsForStructures/T_Set.c)
set(TEST_SIMPLE Tests/TestForSimpleFucntions/T_SimpleFunctions.c)
set(TEST_LEX Tests/TestsForModules/T_B_LexAnalyzer.c)
set(TEST_SYNTAX Tests/TestsForModules/T_C_SyntaxAnalyzer.c)
set(TEST_RISC Tests/TestsForModules/T_R_RISC.c)

add_executable(test_test ${TEST})
add_executable(main ${MAIN})
add_executable(test_struct_tokens ${TEST_TOKENS})
add_executable(test_struct_set ${TEST_SET})
add_executable(test_simple ${TEST_SIMPLE})
add_executable(test_module_lex ${TEST_LEX})
add_executable(test_module_syntax ${TEST_SYNTAX})
add_executable(test_module_risc ${TEST_RISC})

target_link_libraries(test_test lib)
target_link_libraries(main lib)
target_link_libraries(test_struct_tokens lib)
target_link_libraries(test_struct_set lib)
target_link_libraries(test_simple lib)
target_link_libraries(test_module_lex lib)
target_link_libraries(test_module_syntax lib)
target_link_libraries(test_module_risc lib)
target_link_libraries(main m)