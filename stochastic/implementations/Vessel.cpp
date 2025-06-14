//
// Created by Jonathan on 01-06-2025.
//

#include "Vessel.h"

void Vessel::add(const Reaction &r) {
    reactions.push_back(r);
}

std::shared_ptr<Agent> Vessel::add(const std::string &name, const int initialValue) {
    return state.add(name, initialValue);
}

const std::vector<Reaction> &Vessel::getReactions() const {
    return reactions;
}

const SymbolTable &Vessel::getSymbolTable() const {
    return state;
}

std::vector<std::string> Vessel::getAgents() const {
    std::vector<std::string> keys;
    for (const auto& pair : state) {
        keys.push_back(pair.first);
    }
    return keys;
}

SymbolTable &Vessel::environment() {
    return state;
}

void Vessel::prettyPrint(std::ostream& os) const {
    for (const auto& reaction : reactions) {
        os << reaction << std::endl;
    }
}






