//
// Created by Jonathan on 01-06-2025.
//

#include "Reactant.h"
#include "SymbolTable.h"

std::shared_ptr<Reactant> SymbolTable::get(const std::string &name) const {
    if (table.contains(name))
        return table.at(name);

    throw std::exception();
}
std::shared_ptr<Reactant> SymbolTable::add(const std::string &name, int initialValue) {
    if (table.contains(name))
        throw std::exception();

    auto reactant = std::make_shared<Reactant>(name, initialValue);
    table[name] = reactant;
    return reactant;
}

void SymbolTable::increment(const std::string &name) {
    if (table.contains(name)) {
        table[name]->count += 1;
    } else {
        throw std::exception();
    }
}

void SymbolTable::decrement(const std::string &name) {
    if (table.contains(name)) {
        table[name]->count -= 1;
    } else {
        throw std::exception();
    }
}

bool SymbolTable::contains(const std::string &name) const {
    return table.contains(name);
}



