#include "json_output.hpp"
#include "meta.hpp"
#include "data.hpp"

#include <doctest/doctest.h>

#include <sstream>
#include <vector>

using namespace std::string_literals;

/** Output operator just for friendly output in tests: */
std::ostream& operator<<(std::ostream& os, const Aggregate& agg)
{
    json_ostream{os} << agg;
    return os;
}

/** Output operator just for friendly output in tests: */
std::ostream& operator<<(std::ostream& os, const Nested& nested)
{
    json_ostream{os} << nested;
    return os;
}

TEST_CASE("JSON output")
{
    auto os = std::ostringstream{};
    auto jos = json_ostream{os};
    SUBCASE("boolean: lvalue true")
    {
        const auto v = true;
        jos << v;
        CHECK(os.str() == "true");
    }
    SUBCASE("boolean: lvalue false")
    {
        const auto v = false;
        jos << v;
        CHECK(os.str() == "false");
    }
    SUBCASE("boolean: rvalue")
    {
        jos << true;
        CHECK(os.str() == "true");
    }
    SUBCASE("integer")
    {
        jos << 7;
        CHECK(os.str() == "7");
    }
    SUBCASE("double")
    {
        jos << 3.14;
        CHECK(os.str() == "3.14");
    }
    SUBCASE("c-string")
    {
        jos << "hello";
        CHECK(os.str() == "\"hello\"");
    }
    SUBCASE("cpp-string")
    {
        jos << "hello"s;
        CHECK(os.str() == "\"hello\"");
    }
    SUBCASE("container")
    {
        const auto v = std::vector{3, 7, 11};
        jos << v;
        CHECK(os.str() == "[3,7,11]");
    }
    static_assert(accepts_v<const Aggregate&, json_writer>, "const Aggregate should accept writer");
    static_assert(accepts_v<const Nested&, json_writer>, "const Nested should accept writer");
    // TODO: uncomment the following extra tests for meta library and fix accepts_v implementation
    static_assert(!accepts_v<json_writer, Aggregate>, "writer should not accept Aggregate");
    static_assert(!accepts_v<int, double>, "int should not accept double");
    SUBCASE("Aggregate")
    {
        const auto v = Aggregate{true, 3, 3.14, "hello", {7, 11}};
        jos << v;
        CHECK(os.str() == R"({"b":true,"x":3,"y":3.14,"z":"hello","w":[7,11]})");
    }
    SUBCASE("Nested")
    {
        const auto v = Nested{"complicated", {true, 3, 3.14, "hello", {7, 11}}};
        jos << v;
        CHECK(os.str() == R"({"text":"complicated","agg":{"b":true,"x":3,"y":3.14,"z":"hello","w":[7,11]}})");
    }
}
