//
// Created by Jonathan on 01-06-2025.
//
#include "Simulator.h"
#include "Agent.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <future>
#include <Vessel.h>

void Simulator::simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state) {
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

        if (writeToFile) {
            writeCsvRow(time, state);
        }
    }
}

SymbolTable Simulator::simulate(std::vector<Reaction> reactions, const double endTime, SymbolTable state, const int threadCount) const {
    std::vector<std::future<SymbolTable>> futures;

    for (int i = 0; i < threadCount; ++i) {
        futures.emplace_back(std::async(std::launch::async, [=, &reactions, this]() mutable -> SymbolTable {
            Vessel vesselCopy = vessel;
            Simulator threadSim(vesselCopy);
            threadSim.simulate(reactions, endTime, state);
            return state;
        }));
    }

    std::vector<SymbolTable> results;
    for (auto& future : futures) {
        results.push_back(future.get());
    }

    SymbolTable average;
    std::unordered_map<std::string, double> accumulator;

    for (const auto& st : results) {
        for (const auto& [name, value] : st) {
            accumulator[name] += value.get()->count;
        }
    }

    for (const auto& [name, total] : accumulator) {
        average.add(name, total / threadCount);
    }

    return average;
}

void Simulator::openCsvFile(const std::string& filename) {
    if (csvFile.is_open()) {
        csvFile.close();
    }
    csvFile.open(filename);
    if (!csvFile.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }
    auto agents = vessel.getAgents();
    bool first = true;
    csvFile << "time,";
    for (auto& agent : agents) {
        if (!first) {
            csvFile << ",";
        }
        csvFile << agent;
        first = false;
    }
    csvFile << std::endl;
}

void Simulator::writeCsvRow(const double time, const SymbolTable &state) {
    bool first = true;
    csvFile << std::to_string(time) + ",";
    for (const auto pair : state) {
        if (!first) {
            csvFile << ",";
        }
        csvFile << pair.second->count;
        first = false;
    }
    csvFile << std::endl;
}

// std::coroutine_handle<> Simulator::monitorAgent(const std::string& agentName) {
//     int max_val = 0;
//
//     while (true) {
//         max_val = std::max(max_val, vessel.getSymbolTable().get(agentName)->count);
//         co_yield max_val;  // yield the new maximum each step
//     }
// }

// coro::task<int> Simulator::lazy_max(const std::string& agentName, std::function<bool()> isSimulationDone)
// {
//     int maxValue = 0;
//
//     while (!isSimulationDone()) {
//         co_await std::suspend_always{};
//
//         if (auto symbol = vessel.getSymbolTable().get(agentName)) {
//             maxValue = std::max(maxValue, symbol->count);
//         }
//     }
//     co_yield maxValue;
// }