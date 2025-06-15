//
// Created by Jonathan on 01-06-2025.
//

#include "SymbolTable.h"
#include "Agent.h"

Agent SymbolTable::get(const std::string &name) const {
    if (table.contains(name))
        return table.at(name);

    throw std::runtime_error("SymbolTable::get: Symbol not found");
}

Agent SymbolTable::add(const std::string &name, const int initialValue) {
    if (table.contains(name))
        throw std::runtime_error("SymbolTable::add: Symbol already exists");

    auto agent = Agent (name, initialValue);
    table[name] = agent;
    return agent;
}

void SymbolTable::increment(const std::string &name) {
    if (table.contains(name)) {
        table[name].count += 1;
    } else {
        throw std::runtime_error("SymbolTable::increment: Symbol not found");
    }
}

void SymbolTable::decrement(const std::string &name) {
    if (table.contains(name)) {
        if (table[name].count > 0) {
            table[name].count -= 1;
        } else {
            throw std::runtime_error("SymbolTable::decrement: Cannot decrement 0");
        }
    } else {
        throw std::runtime_error("SymbolTable::decrement: Symbol not found");
    }
}

bool SymbolTable::contains(const std::string &name) const {
    return table.contains(name);
}

size_t SymbolTable::size() const {
    return table.size();
}



