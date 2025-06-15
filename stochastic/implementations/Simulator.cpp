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
        csvFile << pair.second.count;
        first = false;
    }
    csvFile << std::endl;
}