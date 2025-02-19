add_executable(main main.cpp)
target_link_libraries(main PRIVATE number_series)
add_test(NAME main COMMAND main)

add_executable(number_series_test number_series_test.cpp)
target_link_libraries(number_series_test PRIVATE number_series doctest::doctest_with_main)
add_test(NAME number_series_test COMMAND number_series_test)

add_executable(sort_bm sort_bm.cpp)
target_link_libraries(sort_bm PRIVATE benchmark::benchmark_main)
add_test(NAME sort_bm COMMAND sort_bm)

add_executable(number_series_bm number_series_bm.cpp)
target_link_libraries(number_series_bm PRIVATE number_series benchmark::benchmark_main)
add_test(NAME number_series_bm COMMAND number_series_bm)

set_tests_properties(sort_bm number_series_bm PROPERTIES RUN_SERIAL TRUE)
