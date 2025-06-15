//
// Created by Jonathan on 01-06-2025.
//
#include "Reaction.h"
#include "Agent.h"
#include <limits>

void Reaction::calculate_delay(std::mt19937 &random_seed, const SymbolTable &state) {
    auto quantity_val = 1.0;
    // For each input agent of a reaction
    for (const auto& input : inputs) {
        // Determine the quantity in the current state of input
        auto quantity = state.get(input->name).count;
        // If none set to infinity
        if (quantity <= 0) {
            delay = std::numeric_limits<double>::infinity();
        }
        // If a single quantity is 0, the reaction is ignored.
        // Computes probability - higher quantity is higher probability
        quantity_val *= quantity;
    }
    const auto exp_input = rate * quantity_val;
    std::exponential_distribution<> d(exp_input);
    delay = d(random_seed);
}

// R2
// Pretty printing of reactions
// Result in format: "[Input agents] --(Rate)--> [Output agents]"
std::ostream& operator<<(std::ostream& os, const Reaction& reaction) {
    //Print input agents
    if (!reaction.inputs.empty()) {
        os << "[";
        os << reaction.inputs[0];
        for (size_t i = 1; i < reaction.inputs.size(); ++i) {
            os << " + " << reaction.inputs[i];
        }
        os << "]";
    }

    //Print rate
    os << " --(" << reaction.rate << ")--> ";

    //Print output agents
    os << "[";
    if (!reaction.outputs.empty()) {
        os << reaction.outputs[0];
        for (size_t i = 1; i < reaction.outputs.size(); ++i) {
            os << " + " << reaction.outputs[i];
        }
    } else {
        os << "Empty";
    }
    os << "]";

    return os;
}