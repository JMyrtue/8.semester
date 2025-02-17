#ifndef POLYLINE_H
#define POLYLINE_H

#include <vector>
#include <iosfwd>
#include <memory>

typedef std::pair<int, int> Point;

class Polyline {
public:
    Point& operator+=(Point p);
    operator bool() const;
    friend std::ostream& operator<<(std::ostream& os, const Polyline& poly);
    std::shared_ptr<std::vector<Point>> storage = std::make_shared<std::vector<Point>>();
};


#endif //POLYLINE_H
