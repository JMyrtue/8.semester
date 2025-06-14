//
// Created by Jonathan on 12-06-2025.
//

#ifndef REACTANT_H
#define REACTANT_H
#include <vector>

#include "Agent.h"

class ReactantGroup {
    std::vector<std::shared_ptr<Agent>> agents {};

public:
    std::vector<std::shared_ptr<Agent>> getAgents() const;
    ReactantGroup(const Agent& a) {agents.push_back(std::make_shared<Agent>(a));}
    ReactantGroup(const Agent& a, const Agent& b) {agents.push_back(std::make_shared<Agent>(a)), agents.push_back(std::make_shared<Agent>(b));}
    ReactantGroup(ReactantGroup r, const Agent& a) { agents = move(r.agents); agents.push_back(std::make_shared<Agent>(a));}

};

inline ReactantGroup operator+(const std::shared_ptr<Agent> &lhs, const std::shared_ptr<Agent> &rhs) {
    return ReactantGroup {*lhs, *rhs};
}

inline ReactantGroup operator+(const ReactantGroup& lhs, const Agent& rhs) {
    return ReactantGroup {lhs, rhs};
}
#endif //REACTANT_H
