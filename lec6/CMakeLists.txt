cmake_minimum_required(VERSION 3.30)
project(lec6)

set(CMAKE_CXX_STANDARD 20)

add_executable(lec6 main.cpp
        Base.cpp
        Base.h
        Derived.cpp
        Derived.h)
