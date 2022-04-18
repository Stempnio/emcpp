cmake_minimum_required(VERSION 3.21)
project(zadania_rozwiazania)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR "/opt/homebrew/opt/boost")
set(Boost_LIBRARY_DIR "/opt/homebrew/Cellar/boost/1.78.0_1/lib")
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(lab1 lab1/main.cpp)

add_executable(lab2_ex1 lab2/Ex1_StaticContainer.cpp)
add_executable(lab2_ex2 lab2/Ex2_StaticContainer2.cpp)
add_executable(lab2_ex3 lab2/Ex3_DynamicContainer.cpp)
add_executable(lab2_ex4 lab2/Ex4_String.cpp)

add_executable(lab3_ex1 lab3/function_pointers.cpp)
add_executable(lab3_ex2 lab3/lambda_expressions.cpp)
add_executable(lab3_ex3 lab3/Printer.cpp)

add_executable(lab4_ex1 lab4/ex_4_1_templates.cpp)
add_executable(lab4_ex2 lab4/ex_4_2_compare.cpp)
add_executable(lab4_ex3 lab4/ex_4_3_selectIf.cpp)

add_executable(lab5_ex1 lab5/ex1_Pair.cpp)
add_executable(lab5_ex2 lab5/ex2_staticVector.cpp lab5/staticVector.h)
add_executable(lab5_ex3 lab5/ex3_dynamicVector.cpp lab5/dynamicVector.h)
add_executable(lab5_ex4 lab5/ex4_conversion.cpp)

add_executable(lab6_ex1 lab6/ex1_variadicFunctions.cpp)
add_executable(lab6_ex2 lab6/ex2_proxy.cpp)
add_executable(lab6_ex3 lab6/ex3_Mixins.cpp)
add_executable(lab6_ex4 lab6/ex4_MultiVector.cpp)

add_executable(lab7_ex1 lab7/ex_7_1_Range.cpp)
add_executable(lab7_ex2 lab7/ex_7_2_MatrixModifiers.cpp)
add_executable(lab7_ex3 lab7/ex_7_3_MatrixIterator.cpp)
add_executable(lab7_ex4 lab7/ex_7_4_Filter.cpp)