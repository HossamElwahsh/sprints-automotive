cmake_minimum_required(VERSION 3.24)
project(BalancedParentheses C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(balanced
        balanced.c
        balanced.h
        main.c
        main.h
        stack.c
        stack.h)