//
// Created by Jonathan on 01-06-2025.
//

#ifndef VESSEL_H
#define VESSEL_H
#include <vector>

#include "SymbolTable.h"
#include "Reaction.h"

class Reaction;

class Vessel {
    SymbolTable state;
    std::vector<Reaction> reactions;

public:
    std::string name;

    explicit Vessel(std::string name_) : name(std::move(name_)) {}

    // Add agent to symbol table
    Agent add(const std::string& name, int initialValue);
    // Add reaction
    void add(const Reaction& r);

    const std::vector<Reaction>& getReactions() const;
    const SymbolTable& getSymbolTable() const;
    std::vector<std::string> getAgents() const;
    SymbolTable& environment();

    //R2
    void prettyPrint(std::ostream& os) const;
    void writeReactionNetwork(const std::string& filename) const;
};

#endif //VESSEL_H
