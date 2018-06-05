cmake_minimum_required(VERSION 3.9)
project(OberonsCompiler C)

set(CMAKE_C_STANDARD 11)

#add_executable(OberonsCompiler main.c)
#add_executable(OberonsCompiler Tests/TestsForModules/T_B_LeksAnalyzer/T_B_LeksAnalyzer.c)

#TODO
#Вот это почему-то работает
#add_executable(OberonsCompiler Tests/TestsForStructures/T_A_Tokens/T_Tokens.c)
#А это нет
add_executable(OberonsCompiler Tests/TestsForStructures/T_C_DeclaredVariables/T_DeclaredVariables.c)
