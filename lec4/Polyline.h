#ifndef POLYLINE_H
#define POLYLINE_H

#include <vector>
#include <iosfwd>

typedef std::pair<int, int> Point;

class Polyline {
    std::vector<Point> sequence{};
public:
    Polyline& operator+=(Point p);
    operator bool();
    friend std::ostream& operator<<(std::ostream& os, const Polyline& poly);
};


#endif //POLYLINE_H
