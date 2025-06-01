//
// Created by Jonathan on 01-06-2025.
//

#ifndef REACTANT_H
#define REACTANT_H
#include <string>

class Reactant {
public:
    std::string name;
    int count;

    explicit Reactant(std::string name_, int count_ = 0) : name(std::move(name_)), count(count_) {}
};

#endif //REACTANT_H
