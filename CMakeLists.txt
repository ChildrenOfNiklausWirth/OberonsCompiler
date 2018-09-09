cmake_minimum_required(VERSION 3.9)
project(OberonsCompiler_C)

set(CMAKE_C_STANDARD 11)

set(LIBRARIES
        Modules/Structures/TerminalSymbols.c
        Modules/Structures/Tokens.c
        Modules/Structures/LongList.c
        Modules/LexAnalyzer.c
        Modules/SyntaxAnalyzer.c
        Modules/CodeGenerator.c
        Modules/SimpleFunctions/SimpleFunctions.c
        Modules/Structures/Node.c
        Modules/Structures/Set.c
        Modules/RISC.c
        )


add_library(lib STATIC ${LIBRARIES})

set(MAIN main.c)
set(TEST_TOKENS Tests/TestsForStructures/T_Tokens.c)
set(TEST_SET Tests/TestsForStructures/T_Set.c)
set(TEST_LEX Tests/TestsForModules/T_B_LexAnalyzer.c)
set(TEST_SYNTAX Tests/TestsForModules/T_C_SyntaxAnalyzer.c)
set(TEST_ED Tests/TestsForModules/T_D_EncodingAndDecoding.c)
set(TEST_CGRI Tests/TestsForModules/T_Z_CodeGenerationAndExecuting.c)

add_executable(main ${MAIN})
add_executable(test_struct_tokens ${TEST_TOKENS})
add_executable(test_struct_set ${TEST_SET})
add_executable(test_module_lex ${TEST_LEX})
add_executable(test_module_syntax ${TEST_SYNTAX})
add_executable(test_module_encodingAndDecoding ${TEST_ED})
add_executable(test_module_codeGenerationAndRiscInterpeter ${TEST_CGRI})


target_link_libraries(main lib)
target_link_libraries(test_struct_tokens lib)
target_link_libraries(test_struct_set lib)
target_link_libraries(test_module_lex lib)
target_link_libraries(test_module_syntax lib)
target_link_libraries(test_module_encodingAndDecoding lib)
target_link_libraries(test_module_codeGenerationAndRiscInterpeter lib)
target_link_libraries(main m)