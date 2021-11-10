cmake_minimum_required(VERSION 3.20)
project(homework2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static")

add_executable(homework2 hw2.cpp)
