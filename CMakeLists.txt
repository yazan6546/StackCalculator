cmake_minimum_required(VERSION 3.30)
project(StackCalculator)

set(CMAKE_CXX_STANDARD 20)
#
add_executable(StackCalculator main.c
        dynamic_array.c
        dynamic_array.h
        Stack.c
        Stack.h)


add_executable(test test.c dynamic_array.c Stack.c)