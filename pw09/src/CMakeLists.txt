cmake_minimum_required(VERSION 3.22)
project(ASD2022_L8_AVL_Tree)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,alignment -fstack-protector -fno-sanitize-recover=null")

add_executable(AVL-Tree main.cpp)
add_subdirectory(catch2_tests)