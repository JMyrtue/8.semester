#include "Polyline.h"
#include <iostream>

int main() {

    Polyline polyline;

    polyline += {1, 1};

    std::cout << polyline << std::endl;
    return 0;
}

