//
// Created by Jonathan on 13-06-2025.
//

#include <iostream>
#include <Simulator.h>
#include <Vessel.h>

int main() {
    auto Nnj = 589755, Ndk = 5822763;
    auto N = 10000;
    auto v = Vessel("Example3");

    const auto eps = 0.0009;                               // initial fraction of infectious
    const auto I0 = size_t(std::round(eps * N));           // initial infectious
    const auto E0 = size_t(std::round(eps * N * 15));      // initial exposed
    const auto S0 = N - I0 - E0;            // initial susceptible

const auto R0 = 2.4;                                       // initial basic reproductive number
    const auto alpha = 1.0 / 5.1;                    // incubation rate (E -> I) ~5.1 days
    const auto gamma = 1.0 / 3.1;                    // recovery rate (I -> R) ~3.1 days
    const auto beta = R0 * gamma;                    // infection/generation rate (S+I -> E+I)
    const auto P_H = 0.9e-3;                               // probability of hospitalization
    const auto kappa = gamma * P_H * (1.0 - P_H);    // hospitalization rate (I -> H)
    const auto tau = 1.0 / 10.12;                    // removal rate in hospital (H -> R)

    const auto S = v.add("S", S0);
    const auto E = v.add("E", E0);
    const auto I = v.add("I", I0);
    const auto H = v.add("H", 0);
    const auto R = v.add("R", 0);

    v.add((S + I) >> beta / N >>= E + I);          // susceptible becomes exposed by infectious
    v.add(E >> alpha >>= I);                       // exposed becomes infectious
    v.add(I >> gamma >>= R);                         // infectious becomes removed
    v.add(I >> kappa >>= H);                       // infectious becomes hospitalized
    v.add(H >> tau >>= R);                           // hospitalized becomes removed

    auto sim = Simulator(v);
    v.prettyPrint(std::cout);

    auto avg_state = sim.simulate(v.getReactions(), 100.0, v.getSymbolTable(), 5);
    std::cout << avg_state.get("H").count;

    // Requirement 7 - Observer
    // auto max = 0;
    // sim.simulate_with_observe(v.getReactions(), 100.0, v.getSymbolTable(), [&max](const int current) {max = std::max(max, current);});
    // std::cout << max << std::endl;


    return 0;
}
