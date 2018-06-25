cmake_minimum_required(VERSION 3.9)
project(OberonsCompiler_C)

set(CMAKE_C_STANDARD 11)

set(LIBRARIES Modules/Structures/B_TerminalSymbols.c Modules/Structures/A_Tokens_And_DV.c Modules/B_LexAnalyzer.c
        Modules/SimpleFunctions/SimpleFunctions.c)

add_library(lib STATIC ${LIBRARIES})

set(TEST test.c)
set(MAIN main.c)
set(TEST_TOKENS Tests/TestsForStructures/T_A_Tokens_and_DV/T_Tokens.c)
set(TEST_DV Tests/TestsForStructures/T_A_Tokens_and_DV/T_DeclaredVariables.c)
set(TEST_LEX Tests/TestsForModules/T_B_LexAnalyzer.c)


add_executable(main ${MAIN})
add_executable(test_test ${TEST})
add_executable(test_struct_tokens ${TEST_TOKENS})
add_executable(test_struct_dv ${TEST_DV})
add_executable(test_module_lex ${TEST_LEX})

target_link_libraries(main lib)
target_link_libraries(test_struct_tokens lib)
target_link_libraries(test_struct_dv lib)
target_link_libraries(test_module_lex lib)
target_link_libraries(test_test lib)