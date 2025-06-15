//
// Created by Jonathan on 13-06-2025.
//

#include <Agent.h>
#include <SymbolTable.h>

#include "doctest/doctest.h"

TEST_CASE("SymbolTable tests") {
    auto st = SymbolTable();

    st.add("A", 0);
    st.add("B", 2);
    st.add("C", 5);

    SUBCASE("SymbolTable default values") {
        CHECK(st.get("A").count == 0);
        CHECK(st.get("B").count == 2);
        CHECK(st.get("C").count == 5);
        CHECK_THROWS(st.get("D"));
        CHECK(st.size() == 3);
    }

    st.add("D", 0);

    SUBCASE("SymbolTable add") {
        CHECK(st.size() == 4);
        CHECK(st.get("D").count == 0);
        CHECK_THROWS(st.add("A", 0));
    }

    st.increment("A");
    st.increment("B");
    st.increment("C");

    SUBCASE("SymbolTable increment") {
        CHECK(st.get("A").count == 1);
        CHECK(st.get("B").count == 3);
        CHECK(st.get("C").count == 6);
        CHECK(st.get("D").count == 0);
    }

    st.decrement("A");
    st.decrement("B");

    SUBCASE("SymbolTable decrement") {
        CHECK(st.get("A").count == 0);
        CHECK(st.get("B").count == 2);
        CHECK(st.get("C").count == 6);
        CHECK_THROWS(st.decrement("D"));
    }
}