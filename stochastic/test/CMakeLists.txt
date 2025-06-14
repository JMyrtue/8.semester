
add_executable(tests test_SymbolTable.cpp test_Vessel.cpp)

target_link_libraries(tests
        stochastic  # Link against your library
        doctest::doctest_with_main # Link against the doctest interface library
)

#include(CTest)
add_test(NAME StochasticTests COMMAND tests)

## Optional: Set properties for the test executable
#set_target_properties(tests PROPERTIES
#        CXX_STANDARD 23 # Ensure consistent C++ standard
#)