cmake_minimum_required(VERSION 3.24)
project(LCS C)

set(CMAKE_C_STANDARD 11)

add_executable(LCS main.c Sort/sort.c main.h LCS/lcs.c)
