add_executable(example1 example1.cpp)
target_include_directories(example1 PRIVATE ../examples)
target_link_libraries(example1 PRIVATE stochastic)