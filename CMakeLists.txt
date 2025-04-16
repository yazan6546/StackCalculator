cmake_minimum_required(VERSION 3.30)
project(StackCalculator)

set(CMAKE_CXX_STANDARD 20)
#
add_executable(StackCalculator src/main.c
        src/dynamic_array.c
        src/Stack.c
        src/utils.c
        )


add_executable(test src/test.c src/dynamic_array.c src/Stack.c)

include_directories(include)