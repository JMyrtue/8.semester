//
// Created by Jonathan on 01-06-2025.
//

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <memory>
#include <string>
#include <unordered_map>

class Reactant;

class SymbolTable {
    std::unordered_map<std::string, std::shared_ptr<Reactant>> table;

public:
    std::shared_ptr<Reactant> get(const std::string& name) const;
    std::shared_ptr<Reactant> add(const std::string& name, int initialValue);
    void increment(const std::string& name);
    void decrement(const std::string& name);
    bool contains(const std::string& name) const;
};

#endif //SYMBOLTABLE_H
