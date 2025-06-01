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
    std::shared_ptr<Reactant> add(const std::string& name, int initialValue);
    void add(const Reaction& r);
    const std::vector<Reaction>& getReactions() const;
    const SymbolTable& getSymbolTable() const;
};

#endif //VESSEL_H
