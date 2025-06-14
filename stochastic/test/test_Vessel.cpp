//
// Created by Jonathan on 13-06-2025.
//
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
}