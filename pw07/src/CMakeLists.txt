cmake_minimum_required(VERSION 3.16)
project(ASD2022_Expressions-arithmetiques)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

add_executable(L8-Dijkstra main.cpp evaluator.cpp)
add_executable(L8-Recursive main.cpp evaluator_recursive.cpp)