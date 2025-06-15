//
// Created by Jonathan on 01-06-2025.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <fstream>
#include <Vessel.h>
#include <algorithm>

#include "Reaction.h"
#include "SymbolTable.h"

class Vessel;

class Simulator {
    Vessel vessel;
    double currentTime = 0.0;

    bool writeToFile;
    std::ofstream csvFile;

public:
    explicit Simulator(Vessel v, const bool writeToFile = false) : vessel(v), writeToFile(writeToFile) {};
    void simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state);
    template<typename Observer>
    void simulate_with_observe(std::vector<Reaction> reactions, double endTime, SymbolTable state, Observer observer);
    SymbolTable simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state, int threadCount) const;
    void openCsvFile(const std::string& filename);
    void writeCsvRow(double time, const SymbolTable& state);
};

template<typename Observer>
void Simulator::simulate_with_observe(std::vector<Reaction> reactions, double endTime, SymbolTable state, Observer observer) {
    std::mt19937 seed(std::random_device{}());

    double time = 0.0;
    if (writeToFile) {
        openCsvFile("..\\..\\examples\\results\\" +vessel.name + ".csv");
    }

    while (time < endTime) {
        for (auto& reaction : reactions) {
            reaction.calculate_delay(seed, state);
        }

        const auto& next_reaction = *std::ranges::min_element(reactions, {}, [](const Reaction& r) {return r.delay;});
        time += next_reaction.delay;
        for (const auto& input : next_reaction.inputs) {
            state.decrement(input->name);
        }
        for (const auto& output : next_reaction.outputs) {
            state.increment(output->name);
        }
        observer(state.get("H").count);
    }
}

#endif //SIMULATOR_H
