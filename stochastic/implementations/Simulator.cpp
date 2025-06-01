//
// Created by Jonathan on 01-06-2025.
//
#include "Simulator.h"

#include <algorithm>

void Simulator::simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state) {
    std::mt19937 seed(std::random_device{}());

    double time = 0.0;
    while (time < endTime) {
        for (auto reaction : reactions) {
            reaction.calculate_delay(seed, state);
        }

        // auto next_reaction = get_next_reaction(reactions);
        const auto& next_reaction = std::ranges::min_element(reactions, {}, [](const Reaction& r) {return r.delay;});
        time += next_reaction->delay;
        for (const auto& input : next_reaction->inputs) {
            state.decrement(input->name);
        }
        for (const auto& output : next_reaction->outputs) {
            state.increment(output->name);
        }
    }

    // Print / Store / Observe
}