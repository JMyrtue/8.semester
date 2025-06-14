cmake_minimum_required(VERSION 3.30)
project(stochastic)

set(CMAKE_CXX_STANDARD 23)

include(cmake/Test.cmake)

add_library(stochastic STATIC
        implementations/SymbolTable.cpp
        implementations/Simulator.cpp
        implementations/Reaction.cpp
        implementations/Vessel.cpp
        implementations/ReactantGroup.cpp
)

target_include_directories(stochastic PUBLIC headers)

add_subdirectory(examples)
add_subdirectory(test)