cmake_minimum_required(VERSION 3.9)
project(OberonsCompiler C)

set(CMAKE_C_STANDARD 11)

#add_executable(OberonsCompiler main.c)
add_executable(OberonsCompiler Tests/TestsForModules/T_B_LeksAnalyzer.c/T_B_LeksAnalyzer.c)
