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
    int count;

    explicit Agent(std::string name_, int count_ = 0) : name(std::move(name_)), count(count_) {}
};

// std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Agent>& agent);
inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Agent>& agent) {
    os << agent->name;
    return os;
}

#endif //AGENT_H
