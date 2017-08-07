cmake_minimum_required(VERSION 3.7)
project(List)

set(CMAKE_C_STANDARD 99)
set(headers LINEAR_SEQUENCE.h)
set(SOURCE_FILES main.c LINEAR_SEQUENCE.c)
add_executable(linear2 ${SOURCE_FILES})