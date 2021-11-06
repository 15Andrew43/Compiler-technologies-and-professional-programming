cmake_minimum_required(VERSION 3.17)
project(Cpu)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cpu main.cpp stack.cpp stack.h commands.cpp commands.h)