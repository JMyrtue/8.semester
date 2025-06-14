//
// Created by Jonathan on 01-06-2025.
//

#ifndef REACTION_H
#define REACTION_H
#include <limits>
#include <cmath>
#include <memory>
#include <ReactionBuilder.h>
#include <SymbolTable.h>
#include <vector>
#include <random>
#include "ReactantGroup.h"

class Reaction {

public:
    std::vector<std::shared_ptr<Agent>> inputs;
    std::vector<std::shared_ptr<Agent>> outputs;
    double rate;
    double delay;

    Reaction(std::vector<std::shared_ptr<Agent>> in,
             std::vector<std::shared_ptr<Agent>> out,
             double rate)
        : inputs(std::move(in)), outputs(std::move(out)), rate(rate), delay(std::numeric_limits<double>::infinity()) {}

    void calculate_delay(std::mt19937 &random_seed, const SymbolTable &state);
    friend std::ostream& operator<<(std::ostream& os, const Reaction& reaction);
};

inline Reaction operator>>=(const ReactionBuilder &lhs, const ReactantGroup &rhs) {
    return Reaction{lhs.reactantGroup->getAgents(), rhs.getAgents(), lhs.rate};
}

inline Reaction operator>>=(const ReactionBuilder &lhs, const std::shared_ptr<Agent> &rhs) {
    return Reaction(lhs.reactantGroup->getAgents(), std::vector{rhs}, lhs.rate);
}

inline Reaction operator>>=(const ReactionBuilder &lhs, const SymbolTable &rhs) {
    return Reaction{lhs.reactantGroup->getAgents(), {}, lhs.rate};
}

#endif //REACTION_H
