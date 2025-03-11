#ifndef STATIC_VISITOR_META_HPP
#define STATIC_VISITOR_META_HPP
#include <string>
#include <type_traits>

/**
 * TODO: implement meta-predicates
 * (template classes/variables taking type and returning bool)
 * is_bool_v
 * is_number_v
 * is_character_v
 * is_string_v
 * is_container_v
 * accepts_v
 *
 * Tips:
 * - read documentation about std::is_same, std::is_integral, std::is_floating_point, std::is_arithmetic.
 * - make your meta-predicates robust against const/volatile/reference combinations (see meta_test.cpp):
 *   see std::remove_reference, std::remove_const, std::remove_cvref, std::decay
 */

template <typename T>
constexpr auto is_bool_v = std::is_same_v<std::remove_cvref_t<T>, bool>;  // FIXME

template <typename T>
constexpr auto is_number_v = ((std::is_integral_v<std::remove_cvref_t<T>> and !is_bool_v<T>) or
                              std::is_floating_point_v<std::remove_cvref_t<T>>) and
                              std::is_arithmetic_v<std::remove_cvref_t<T>>;  // FIXME

template <typename T>
constexpr auto is_character_v = std::is_same_v<std::remove_cvref_t<T>, char>;  // FIXME

template <typename T>
constexpr auto is_string_v = std::is_same_v<std::remove_cvref_t<T>, std::string> or
                             std::is_same_v<std::remove_cvref_t<T>, char *> or
                             std::is_same_v<std::remove_cvref_t<T>, const char *> or
                             (std::is_array_v<std::remove_cvref_t<T>> and is_character_v<std::remove_extent_t<std::remove_cvref_t<T>>>);
// FIXME: true for std::string, const char*, char*, char[5]

template <typename T>
concept IsContainer = requires (T t)
{
  std::begin(t);
  std::end(t);
} and !is_string_v<T>;

template <typename T>
constexpr auto is_container_v = IsContainer<T>;  // FIXME: use concepts, require std::begin, std::end, and not is_string_v

template <typename Data, typename Visitor>
concept Visitable = requires (Data d, Visitor v) {d.accept(v); };

template <typename Data, typename Visitor>
constexpr auto accepts_v = Visitable<Data, Visitor>;  // FIXME: check for Data::accept(Visitor) by using concepts or detection toolkit

#endif  // STATIC_VISITOR_META_HPP
