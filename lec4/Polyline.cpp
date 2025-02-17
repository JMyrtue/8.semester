#include "Polyline.h"
#include <iostream>

Point& Polyline::operator+=(Point p) {
    if (storage.use_count() > 1) {
        storage = std::make_shared<std::vector<Point>>(*storage);
    }
    storage->push_back(p);
    return storage->back();
}

Polyline::operator bool() const {
    return !storage ->empty();
}

std::ostream& operator<<(std::ostream& os, const Polyline& poly) {
    os << "Polyline@ " << poly.storage.get();
    os << "[";
    for (auto p : *poly.storage) {
        os << "{" << p.first << ", " << p.second << "}";
        os << ",";
    }
    os << "]" << std::endl;
    return os;
}
