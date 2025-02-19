cmake_minimum_required(VERSION 3.15)
project(Extended1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)

include(cmake/sanitizers.cmake)
include(cmake/doctest.cmake)
include(cmake/benchmark.cmake)

include_directories(include)

enable_testing()

add_subdirectory(source)
add_subdirectory(tests)
