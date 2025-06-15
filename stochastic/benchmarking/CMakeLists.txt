add_executable(SimBM SimBenchmark.cpp)
target_link_libraries(SimBM PRIVATE benchmark::benchmark_main stochastic)