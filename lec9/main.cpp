#include <iostream>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream &os, std::vector<T> const &vector) {
    os << '{';
    for (size_t i = 0; i < vector.size(); i++) {
        os << vector[i];
        if (i != vector.size() - 1) { os << ", "; }
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
    std::cout << v << '\n';
    std::cout << dv << '\n';
    std::cout << sv << '\n';

    std::cout << std::vector{std::vector{"hello", "template"}, std::vector{"world"}} << std::endl;

    //TD<decltype(v)> temp;
    return 0;
}