//
// Created by Jonathan on 01-06-2025.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <fstream>
#include <Vessel.h>
#include <algorithm>
#include <future>

#include "Reaction.h"
#include "SymbolTable.h"

class Vessel;

class Simulator {
    Vessel vessel;
    double currentTime = 0.0;

    bool writeToFile;
    std::ofstream csvFile;

    template<typename Observer>
    void actual_simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state, Observer observer);
public:
    explicit Simulator(Vessel v, const bool writeToFile = false) : vessel(v), writeToFile(writeToFile) {};
    // void simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state);
    template<typename Observer>
    std::vector<std::future<SymbolTable>> simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state, Observer observer = []{}, int threadCount = 1) const;
    std::vector<std::future<SymbolTable>> simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state) const;
    std::vector<std::future<SymbolTable>> simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state, int threadCount) const;
    void openCsvFile(const std::string& filename);
    void writeCsvRow(double time, const SymbolTable& state);
};

template<typename Observer>
void Simulator::actual_simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state, Observer observer) {
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
        observer(state);
    }
}

template<typename Observer>
std::vector<std::future<SymbolTable>> Simulator::simulate(std::vector<Reaction> reactions, const double endTime, SymbolTable state, Observer observer, const int threadCount) const {
    std::vector<std::future<SymbolTable>> futures;

    for (int i = 0; i < threadCount; ++i) {
        futures.emplace_back(std::async(std::launch::async, [=, &reactions, this]() mutable -> SymbolTable {
            Vessel vesselCopy = vessel;
            Simulator threadSim(vesselCopy);
            threadSim.actual_simulate(reactions, endTime, state, observer);
            return state;
        }));
    }
    return futures;
}

inline std::vector<std::future<SymbolTable>> Simulator::simulate(std::vector<Reaction> reactions, const double endTime, SymbolTable state, const int threadCount) const {
    return simulate(std::move(reactions), endTime, std::move(state), [](const SymbolTable& _){}, threadCount);
}


inline std::vector<std::future<SymbolTable>> Simulator::simulate(std::vector<Reaction> reactions, const double endTime, SymbolTable state) const {
    return simulate(std::move(reactions), endTime, std::move(state), [](const SymbolTable& _){});
}

#endif //SIMULATOR_H
