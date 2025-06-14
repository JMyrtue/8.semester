//
// Created by Jonathan on 13-06-2025.
//

#include <iostream>
#include <Simulator.h>
#include <Vessel.h>

int main() {
    const auto rate = 0.001;

    auto v = Vessel{"Example1"};

    const auto A = v.add("A", 100);
    const auto B = v.add("B", 0);
    const auto C = v.add("C", 2);

    v.add(A + C >> rate >>= B + C);

    auto sim = Simulator(v);
    v.prettyPrint(std::cout);

    sim.simulate(v.getReactions(), 2000.0, v.getSymbolTable());

    return 0;
}
