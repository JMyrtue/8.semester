//
// Created by Jonathan on 12-06-2025.
//

#ifndef AGENT_H
#define AGENT_H
#include <memory>
#include <string>

class Agent {
public:
    std::string name;
    size_t count;

    Agent() = default;
    explicit Agent(std::string name, const size_t count = 0) : name(std::move(name)), count(count) {}
};

// R2
inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Agent>& agent) {
    os << agent->name;
    return os;
}

#endif //AGENT_H
