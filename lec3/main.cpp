#include <algorithm>
#include <cassert>
#include <functional>
#include <random>
#include <vector>
#include <bits/random.h>
#include <bits/ranges_algo.h>

#include "spy.cpp"

Spy make_spy() {
    auto result = Spy();
    return result;
}

// std::ostream& print(Spy spy) { return std::cout << spy; }
std::ostream& print(const Spy& spy) { return std::cout << spy; }

auto arithmetic_progression(const int a0, const int step) {
    return [=](const int i) {return a0 + step * i;};
}

auto just_odd(std::vector<int> v) {
    auto temp = std::vector<int>();
    std::ranges::copy_if(v, std::back_inserter(temp), [](int i) { return i % 2 == 1; });
    return temp;
}

auto arithmetic_sequence(const int a0, const int step) {
    static int i = -1;
    return [=]() {i++; return a0 + step * i;};
}

auto random(const double from, const double till) {
    return [gen = std::mt19937(std::random_device{}()),
            dist = std::uniform_real_distribution<double>(from, till)]() mutable {return dist(gen);};
}

std::function<double(double, int)> ipow = [](double base, int p) {
    if (p < 0)
        return 1 / ipow(base, -p);
    if (p == 0)
        return 1.0;
    else if (p == 1)
        return base;
    else {
        auto result = ipow(base, p/2);
        result *= result;
        if (p % 2 == 1)
            result *= base;
        return result;
    }
};

int main() {
    auto ap = arithmetic_progression(3,2);
    assert(ap(0) == 3);
    assert(ap(1) == 5);
    assert(ap(2) == 7);
    assert(ap(3) == 9);
    assert(ap(4) == 11);
    auto odd = just_odd({0,1,2,3,4,5,6,7,8,9});
    auto res = std::vector{1,3,5,7,9};
    assert(odd == res);

    auto as = arithmetic_sequence(3,2);
    assert(as() == 3);
    assert(as() == 5);
    assert(as() == 7);
    assert(as() == 9);
    auto r10 = random(0,10);
    for (auto i = 0; i < 1000; i++) {
        auto n = r10();
        assert(0 <= n);
        assert(n < 10);
    }

    auto p0 = ipow(2,0);
    assert(p0 == 1);
    auto p1 = ipow(2,1);
    assert(p1 == 2);
    auto p2 = ipow(2,2);
    assert(p2 == 4);
    auto p3 = ipow(2,3);
    assert(p3 == 8);
    auto p4 = ipow(2,-1);
    assert(p4 == 0.5);
    auto p5 = ipow(2,-2);
    assert(p5 == 0.25);

    // auto spy = Spy{};
    // print(spy) << std::endl;
    // print(Spy{}) << std::endl;
    // print(make_spy()) << std::endl;

    // std::cout << "Spy{}: " << Spy{} << std::endl;
    // std::cout << "make_spy(): " << make_spy() << std::endl;
    // auto spy2 = make_spy();
    // std::cout << "spy2: " << spy2 << std::endl;

    // auto spies = std::vector<Spy>();
    // spies.reserve(5);
    // for (int i = 0; i < 5; i++) {
    //     std::cout << "!! adding a spy !!" << std::endl;
    //     spies.push_back(Spy());
    // }
    // for (auto&& spy : spies) {
    //     std::cout << spy << std::endl;
    // }

    return 0;
}
