cmake_minimum_required(VERSION 3.16)
project(ASD2022-L1-Complexite)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -pedantic")

set(
        L1-sortingLibrary
        vector-generator.h
        selection-sort.h
        insertion-sort.h
        bubble-sort.h
        OpCounter.h OpCounterImpl.h
)

add_executable(L1-testSortingAlgos ${L1-sortingLibrary} main-test-algorithms.cpp)
add_executable(L1-timeMeasurement ${L1-sortingLibrary} main-time-measurement.cpp)
add_executable(L1-operationCount ${L1-sortingLibrary} main-operation-count.cpp)

add_executable(L1-example example.cpp)