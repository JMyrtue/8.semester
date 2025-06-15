include(FetchContent)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark's tests" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable benchmark's GTest tests" FORCE)
set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "Disable bundled GTest" FORCE)
FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.4
)
FetchContent_MakeAvailable(benchmark)