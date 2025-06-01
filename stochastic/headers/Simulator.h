//
// Created by Jonathan on 01-06-2025.
//

#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "Reaction.h"
#include "SymbolTable.h"

class Vessel;

class Simulator {
    Vessel& vessel;
    double currentTime = 0.0;

public:
    explicit Simulator(Vessel& v) : vessel(v) {};
    void simulate(std::vector<Reaction> reactions, double endTime, SymbolTable state);
};

#endif //SIMULATOR_H
