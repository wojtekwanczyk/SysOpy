cmake_minimum_required(VERSION 3.7)
project(zad1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c sblocks.h sblocks.c dblocks.c dblocks.h dmain.c)
add_executable(zad1 ${SOURCE_FILES})