
add_executable(tests test_SymbolTable.cpp test_Vessel.cpp)

target_link_libraries(tests
        stochastic  # Link against your library
        doctest::doctest_with_main # Link against the doctest interface library
)

add_test(NAME StochasticTests COMMAND tests)
