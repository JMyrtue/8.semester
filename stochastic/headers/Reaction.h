//
// Created by Jonathan on 01-06-2025.
//

#ifndef REACTION_H
#define REACTION_H
#include <memory>
#include <Reactant.h>
#include <SymbolTable.h>
#include <vector>
#include <bits/random.h>

class Reactant;

class Reaction {


public:
    std::vector<std::shared_ptr<Reactant>> inputs;
    std::vector<std::shared_ptr<Reactant>> outputs;
    double rate;
    double delay;

    Reaction(std::vector<std::shared_ptr<Reactant>> in,
             std::vector<std::shared_ptr<Reactant>> out,
             double lambda)
        : inputs(std::move(in)), outputs(std::move(out)), rate(lambda), delay(0) {}

    void calculate_delay(std::mt19937 random_seed, const SymbolTable &state);
};

#endif //REACTION_H
