set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic --coverage")
add_executable(AVL-tests avlTest.cpp catch_main.cpp)