//
// Created by Jonathan on 01-06-2025.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <fstream>
#include <Vessel.h>
#include <algorithm>
#include <future>
#include <iostream>

#include "Reaction.h"
#include "SymbolTable.h"

class Vessel;

class Simulator {
    Vessel vessel;
    double currentTime = 0.0;

    bool writeToFile;
    std::ofstream csvFile;

    template<typename Observer>
    void actual_simulate(std::vector<Reaction> reactions, double endTime, SymbolTable &state, Observer observer);
public:
    explicit Simulator(Vessel v, const bool writeToFile = false) : vessel(v), writeToFile(writeToFile) {};

    template<typename Observer>
    std::vector<std::future<SymbolTable>> simulate(const std::vector<Reaction>& reactions, double endTime, Observer observer = []{}, int threadCount = 1) const;
    std::vector<std::future<SymbolTable>> simulate(const std::vector<Reaction>& reactions, double endTime) const;
    std::vector<std::future<SymbolTable>> simulate(const std::vector<Reaction>& reactions, double endTime, int threadCount) const;

    void openCsvFile(const std::string& filename);
    void writeCsvRow(double time, const SymbolTable& state);
};

// Methods hereunder only placed because generic observer does not allow for definition in cpp
// Actual simulation of Algorithm 1
template<typename Observer>
void Simulator::actual_simulate(std::vector<Reaction> reactions, double endTime, SymbolTable& state, Observer observer) {
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

        // Provides observer with state - observers responsibility hereafter.
        observer(state);

        if (writeToFile) {
            writeCsvRow(time, state);
        }
    }
}

// Wrapper function managing multithreading
template<typename Observer>
std::vector<std::future<SymbolTable>> Simulator::simulate(const std::vector<Reaction>& reactions, const double endTime, Observer observer, const int threadCount) const {
    std::vector<std::future<SymbolTable>> futures;

    for (int i = 0; i < threadCount; ++i) {
        futures.emplace_back(std::async(std::launch::async, [=, reactions, this]() mutable -> SymbolTable {
        try {
            // Copies to ensure each thread is independent
            const Vessel vesselCopy = vessel;
            Simulator threadSim(vesselCopy, writeToFile);
            SymbolTable threadState = vessel.getSymbolTable();

            threadSim.actual_simulate(reactions, endTime, threadState, observer);

            // return state for observer
            return threadState;
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Thread threw: ") + e.what());
            }
        }));
    }
    return futures;
}

// Wrapper for not declaring observer, but declaring thread count
inline std::vector<std::future<SymbolTable>> Simulator::simulate(const std::vector<Reaction>& reactions, const double endTime, const int threadCount) const {
    return simulate(std::move(reactions), endTime, [](const SymbolTable& _){}, threadCount);
}

// Wrapper for neither declaring observer nor thread count
inline std::vector<std::future<SymbolTable>> Simulator::simulate(const std::vector<Reaction>& reactions, const double endTime) const {
    return simulate(std::move(reactions), endTime, [](const SymbolTable& _){});
}

#endif //SIMULATOR_H
