cmake_minimum_required(VERSION 3.15)
project(CalculatorMixedNumbers)

set(CMAKE_CXX_STANDARD 14)

add_executable(CalculatorMixedNumbers main.cpp calculate.cpp calculate.h fraction.cpp fraction.h friendsoffraction.cpp mixednumber.cpp mixednumber.h parseexception.h parser.cpp parser.h streamutilities.cpp streamutilities.h)