cmake_minimum_required(VERSION 3.30)
project(stochastic)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.12
)
FetchContent_MakeAvailable(doctest)

add_library(stochastic STATIC
        implementations/SymbolTable.cpp
        implementations/Simulator.cpp
        implementations/Reaction.cpp
        implementations/Vessel.cpp
)

target_include_directories(stochastic PUBLIC ${PROJECT_SOURCE_DIR}/headers)

add_subdirectory(examples)