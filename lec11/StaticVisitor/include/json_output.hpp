#ifndef STATIC_VISITOR_JSON_OUTPUT_HPP
#define STATIC_VISITOR_JSON_OUTPUT_HPP

#include <iostream>
#include <meta.hpp>
#include <doctest/doctest.h>

/** TODO: implement json_ostream adapter with json output operations
 * The goal is to exercise meta-programming and not have complete JSON (Unicode support is beyond the scope).
 */
struct json_ostream
{
    std::ostream& os;
};

/** Visitor pattern support for writing JSON */
struct json_writer
{
    json_ostream& jos;
    bool first = true;
    template <typename Data>
    void visit(std::string_view name, const Data& value)
    {
        if (!first) {
            jos.os << ',';
        }
        first = false;
        jos.os << "\"" << name << "\":" ;
        jos << value;
        /** TODO: use static visitor pattern to write class fields into output stream */
    }
};

template <typename T>
json_ostream& operator<<(json_ostream& j, const T& value)
{
    /** TODO: implement output of arbitrary types so that tests in json_test pass
     * Focus on one test in json_test at a time: begin from the first and then continue to next.
     * In order to support various types, develop and test meta-predicates (see meta_test.cpp)
     * Tip: either use if-constexpr or overloading with SFINAE/concepts
     */

    if constexpr (is_bool_v<T>) { j.os << (value ? "true" : "false"); }
    else if constexpr (is_number_v<T>) { j.os << value; }
    else if constexpr (is_character_v<T>) { j.os << value; }
    else if constexpr (is_string_v<T>) { j.os << "\"" << value << "\""; }
    else if constexpr (is_container_v<T>)
        { j.os << '[';
        auto it = std::begin(value), e = std::end(value);
        if (it != e) {
            j << *it;
            while (++it != e) {
                j.os << ",";
                j << *it;
            }
        }
        j.os << "]"; }
    else if constexpr (Visitable<T, json_writer>) {
        json_writer jw{j};
        j.os << "{";
        value.accept(jw);
        j.os << "}";
    }

    return j;
}

template <typename T>
json_ostream& operator<<(json_ostream&& j, const T& value)
{
    return j << value;
}

#endif  // STATIC_VISITOR_JSON_OUTPUT_HPP
