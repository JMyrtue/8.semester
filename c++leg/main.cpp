
#include <iostream>

int main() {
    int days;
    std::cin >> days;

    std::string yesterday{};
    std::cin >> yesterday;

    int hangovers = 0;
    std::string today{};
    for (int i = 0; i < days - 1; i++) {
        std::cin >> today;

        if (yesterday == "drunk" && today == "sober") {
            hangovers++;
        }
        yesterday = today;
    }

    std::cout << hangovers;

}
