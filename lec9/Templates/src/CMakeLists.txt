add_executable(kindof_test kindof_test.cpp)
target_link_libraries(kindof_test PRIVATE doctest::doctest_with_main)

add_executable(type_name_test type_name_test.cpp)
target_link_libraries(type_name_test PRIVATE doctest::doctest_with_main)

add_executable(deduction deduction.cpp)
target_link_libraries(deduction PRIVATE doctest::doctest_with_main)

add_executable(fibonacci_test fibonacci_test.cpp)
target_link_libraries(fibonacci_test PRIVATE doctest::doctest_with_main)

add_executable(power_test power_test.cpp)
target_link_libraries(power_test PRIVATE doctest::doctest_with_main)

if (Boost_FOUND)
    add_executable(type_name_boost type_name_boost.cpp)
    target_link_libraries(type_name_boost PRIVATE doctest::doctest_with_main)
    add_test(NAME type_name_boost COMMAND type_name_boost)
endif(Boost_FOUND)

add_test(NAME kindof_test COMMAND kindof_test)
add_test(NAME type_name_test COMMAND type_name_test)
add_test(NAME fibonacci_test COMMAND fibonacci_test)
add_test(NAME power_test COMMAND power_test)
add_test(NAME deduction COMMAND power_test)
