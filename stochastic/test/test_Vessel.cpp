//
// Created by Jonathan on 13-06-2025.
//
#include <iostream>
#include <sstream>
#include <vessel.h>

#include "doctest/doctest.h"

TEST_CASE("Vessel Testcases") {
    auto v = Vessel("TestVessel");
    const auto A = v.add("A", 0);
    const auto B = v.add("B", 1);
    const auto C = v.add("C", 2);

    SUBCASE("Add Agents") {
        CHECK(v.getSymbolTable().size() == 3);
        CHECK_THROWS(v.add("A", 0));
    }

    SUBCASE("Add Reactions") {
        CHECK(v.getReactions().size() == 0);
        v.add(A + B >> 0.1 >>= C);
        CHECK(v.getReactions().size() == 1);
    }

    SUBCASE("Pretty Printing") {
        v.add(A + B >> 0.1 >>= C);
        std::ostringstream oss;
        v.prettyPrint(oss);
        CHECK(oss.str() == "[A + B] --(0.1)--> [C]\n");

        v.add(C >> 0.1 >>= A);
        std::ostringstream oss2;
        v.prettyPrint(oss2);
        CHECK(oss2.str() == "[A + B] --(0.1)--> [C]\n[C] --(0.1)--> [A]\n");
    }
}