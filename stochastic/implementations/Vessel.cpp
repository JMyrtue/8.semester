//
// Created by Jonathan on 01-06-2025.
//

#include "Vessel.h"

void Vessel::add(const Reaction &r) {
    reactions.push_back(r);
}

std::shared_ptr<Reactant> Vessel::add(const std::string &name, const int initialValue) {
    return state.add(name, initialValue);
}

const std::vector<Reaction> &Vessel::getReactions() const {
    return reactions;
}

const SymbolTable &Vessel::getSymbolTable() const {
    return state;
}




