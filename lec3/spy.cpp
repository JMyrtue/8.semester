#include <iostream>

struct Spy {
private:
    int data = 0;
public:
    Spy() {
        std::cout << "Spy constructor" << std::endl;
    }
    ~Spy() {
        std::cout << "Spy destruct" << std::endl;
    }
    Spy(const Spy &other) {
        std::cout << "Spy copy" << std::endl;
    }
    Spy(const Spy &&other) noexcept {
        std::cout << "Spy move" << std::endl;
    }
    Spy& operator=(const Spy &other) {
        std::cout << "Spy copy assign" << std::endl;
        return *this;
    }
    Spy& operator=(Spy &&other) noexcept {
        std::cout << "Spy move assign" << std::endl;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Spy& obj) {
        return os << "Spy{" << obj.data << "}" << std::endl;
    }
};

