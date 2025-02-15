#include "Polyline.h"
#include <iostream>

Polyline& Polyline::operator+=(Point p) {
    sequence.push_back(p);
    return *this;
}

Polyline::operator bool() {
    return sequence.size() > 0;
}

std::ostream& operator<<(std::ostream& os, const Polyline& poly) {
    os << "Polyline@ " << &poly.sequence;
    os << "[";
    for (auto p : poly.sequence) {
        os << "{" << p.first << ", " << p.second << "}";
        os << ",";
    }
    os << "]" << std::endl;
    return os;
}
