//
// Created by Jonathan on 12-06-2025.
//

#ifndef REACTIONBUILDER_H
#define REACTIONBUILDER_H
#include <memory>

#include "ReactantGroup.h"

// Intermediate class for building a reaction. Holds input agents and rate.
class ReactionBuilder {
public:
    std::shared_ptr<ReactantGroup> reactantGroup;
    double rate;

    ReactionBuilder(const std::shared_ptr<ReactantGroup> &reactantGroup, const double rate)
      : reactantGroup(reactantGroup), rate(rate) {}
};

// R1:
// Operator for building reactionbuilder from multiple inputs
inline ReactionBuilder operator>>(const ReactantGroup& input, const double& rate) {
    return ReactionBuilder{std::make_shared<ReactantGroup>(input), rate};
}

// Operator for building reactionbuilder from single input agent
inline ReactionBuilder operator>>(const std::shared_ptr<Agent>& input, const double rate) {
    return ReactionBuilder{std::make_shared<ReactantGroup>(ReactantGroup {*input}), rate};
}


#endif // REACTIONBUILDER_H
