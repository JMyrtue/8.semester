#include <iostream>
#include <vector>

template<typename C, typename = void>
struct is_container : std::false_type {};

template<typename C>
struct is_container <C, std::void_t<typename C::iterator,
                                    typename C::const_iterator,
                                    decltype(std::begin(std::declval<C&>())),
                                    decltype(std::end(std::declval<C&>()))>> : std::true_type {};

template <typename T>
concept is_char = std::same_as<std::remove_cvref_t<T>,char> or std::same_as<T,char8_t>;

template <typename T>
concept not_char = not is_char<T>;

template <typename T>
concept non_string_container = requires(T&& c)
{
    {std::end(c)};
    {*std::begin(c)} -> not_char;
    requires noexcept(c.~T());
} && sizeof(T) <= 32;


//template<typename T, typename = std::enable_if_t<is_container<T>::value && !std::is_same_v<std::remove_cvref_t<T>, std::string>, std::ostream&>>
template<typename T>
std::enable_if_t<is_container<T>::value && !std::is_same_v<std::remove_cvref_t<T>, std::string>, std::ostream&>
//template<non_string_container T>
operator<<(std::ostream &os, const T &container) {
    os << '{';
    for (size_t i = 0; i < container.size(); i++) {
        os << container[i];
        if (i != container.size() - 1) { os << ", "; }
    }
    os << '}';
    return os;
}

template<typename T>
class TD;

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<double> dv = {1.2, 5.4, 4.3, 6.2};
    std::vector sv {"hello", "template"};
    std::vector<std::string> ssv {"Again", "and again"};
    std::cout << v << '\n';
    std::cout << dv << '\n';
    std::cout << sv << '\n';
    std::cout << ssv << '\n';

    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl;

    //TD<decltype(v)> temp;
    return 0;
}