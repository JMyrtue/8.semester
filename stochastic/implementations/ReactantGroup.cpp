//
// Created by Jonathan on 12-06-2025.
//

#include <memory>
#include <ReactantGroup.h>

std::vector<std::shared_ptr<Agent>> ReactantGroup::getAgents() const {
    return agents;
}
