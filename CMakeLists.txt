cmake_minimum_required(VERSION 3.21)
project(zadania_rozwiazania)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 lab1/main.cpp)

add_executable(lab2_ex1 lab2/Ex1_StaticContainer.cpp)
add_executable(lab2_ex2 lab2/Ex2_StaticContainer2.cpp)
add_executable(lab2_ex3 lab2/Ex3_DynamicContainer.cpp)
add_executable(lab2_ex4 lab2/Ex4_String.cpp)

add_executable(lab3_ex1 lab3/function_pointers.cpp)
add_executable(lab3_ex2 lab3/lambda_expressions.cpp)
add_executable(lab3_ex3 lab3/Printer.cpp)