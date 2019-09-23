cmake_minimum_required(VERSION 3.14)
project(calculator)

set(CMAKE_CXX_STANDARD 11)

add_executable(calculator public.h token.h Operand.h TokenFactory.h ExpressionParser.h ExpressionFormatException.h MemoryAllocateException.h Memory.h BinaryExpression.h Lexer.h Calculator.h BaseException.h main.cpp)