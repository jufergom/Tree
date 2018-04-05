cmake_minimum_required(VERSION 3.8)
project(Tree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.cpp Node.h Tree.cpp Tree.h)
add_executable(Tree ${SOURCE_FILES})