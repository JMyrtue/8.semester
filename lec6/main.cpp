#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

#include "Base.h"
#include "Derived.h"

int main() {
    std::vector<std::unique_ptr<Base>> list;
    std::chrono::time_point<std::chrono::system_clock> start1, end1, start2, end2, start3, end3, start4, end4;

    list.reserve(10'000'000);
    for (auto i = 0; i < 10'000'000; i++) {
        list.push_back(std::make_unique<Derived>());
    }
    std::cout << "Size of list: " << list.size() << std::endl;

    start1 = std::chrono::system_clock::now();

    for (auto &n : list) {
        n->increment();
    }
    end1 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end1 - start1;
    std::cout << "Base Vector incremenet: " << elapsed_seconds << std::endl;

    start2 = std::chrono::system_clock::now();
    for (auto &n : list) {
        n->decrement();
    }
    end2 = std::chrono::system_clock::now();
    elapsed_seconds = end2 - start2;
    std::cout << "Base Vector decrement: " << elapsed_seconds << std::endl;

    auto list2 = std::vector<Derived>(10'000'000);
    std::cout << "Size of list2: " << list2.size() << std::endl;

    start3 = std::chrono::system_clock::now();

    for (auto &n : list) {
        n->increment();
    }
    end3 = std::chrono::system_clock::now();
    elapsed_seconds = end3 - start3;
    std::cout << "No pointer incremenet: " << elapsed_seconds << std::endl;

    start4 = std::chrono::system_clock::now();
    for (auto &n : list) {
        n->decrement();
    }
    end4 = std::chrono::system_clock::now();
    elapsed_seconds = end4 - start4;
    std::cout << "No Pointer decrement: " << elapsed_seconds << std::endl;


    std::cout << "Summary: \n" << std::endl;
    elapsed_seconds = end2 - start1;
    std::cout << "Pointer timing: " << elapsed_seconds << std::endl;
    elapsed_seconds = end4 - start3;
    std::cout << "No pointer timing: " << elapsed_seconds << std::endl;

    return 0;
}

