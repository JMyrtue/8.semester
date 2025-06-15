//
// Created by Jonathan on 01-06-2025.
//

#include "Vessel.h"

#include <fstream>

void Vessel::add(const Reaction &r) {
    reactions.push_back(r);
}

Agent Vessel::add(const std::string &name, const int initialValue) {
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

void Vessel::writeReactionNetwork(const std::string &filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    for (const auto& reaction : reactions) {
        out << "(";
        for (size_t i = 0; i < reaction.inputs.size(); ++i) {
            out << reaction.inputs[i]->name;
            if (i < reaction.inputs.size() - 1)
                out << " + ";
        }
        out << ") >> " << reaction.rate << " >>= ";
        for (size_t i = 0; i < reaction.outputs.size(); ++i) {
            out << reaction.outputs[i]->name;
            if (i < reaction.outputs.size() - 1)
                out << " + ";
        }
        out << "\n";
    }
}








