//
// Created by Jonathan on 01-06-2025.
//

#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include <memory>
#include <string>
#include <unordered_map>

class Agent;

class SymbolTable {
    std::unordered_map<std::string, Agent> table;

public:
    Agent get(const std::string& name) const;
    Agent add(const std::string& name, int initialValue);
    void update(const std::string& name, int value);
    void increment(const std::string& name);
    void decrement(const std::string& name);
    bool contains(const std::string& name) const;
    size_t size() const;

    auto begin() {return table.begin();}
    auto begin() const {return table.begin();}
    auto end() {return table.end();}
    auto end() const {return table.end();}
};

#endif //SYMBOLTABLE_H
