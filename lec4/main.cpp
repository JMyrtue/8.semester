#include "Polyline.h"
#include <iostream>
#include <sstream>

void check_content(const Polyline& poly, const bool contains_points) {
    if (contains_points) {
        if (!poly)
            std::cerr << "Unexpected: Polyline does not contain points" << std::endl;
    } else {
        if (poly)
            std::cerr << "Unexpected: Polyline contains points" << std::endl;
    }
}

void check_storage(const Polyline& p1, const Polyline& p2, const bool same) {
    auto os1 = std::ostringstream{};
    auto os2 = std::ostringstream{};
    os1 << p1;
    os2 << p2;
    if (same) {
        if (os1.str() != os2.str())
            throw std::logic_error("Unexpected: p1 and p2 differ");
    } else {
        if (os1.str() == os2.str())
            throw std::logic_error("Unexpected: p1 and p2 equal");
    }
}

int main()
try {
    auto poly1 = Polyline{};
    check_content(poly1, false);
    poly1 += Point{1, 1};
    check_content(poly1, true);
    auto poly2 = poly1;
    check_content(poly2, true);
    check_storage(poly1, poly2, true);
    poly2 += Point{2, 2};
    check_storage(poly1, poly2, false);
    auto poly3 = poly2;
    check_content(poly3, true);
    check_storage(poly2, poly3, true);
    poly3 += Point{3, 3};
    check_storage(poly2, poly3, false);
    check_storage(poly1, poly3, false);
    poly1 = poly3;
    check_storage(poly1, poly3, true);
    poly2 = std::move(poly3); // don't use poly3 without re-assignment
    check_storage(poly1, poly2, true);
    poly3 = poly2; // now poly3 is in a good state
    check_storage(poly1, poly3, true);
    return 0;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
} catch (...) {
    std::cerr << "Unexpected exception" << std::endl;
    return 1;
}

