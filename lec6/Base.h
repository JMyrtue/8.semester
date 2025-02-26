//
// Created by toyot on 21-02-2025.
//

#ifndef BASE_H
#define BASE_H



class Base {
public:
    int num = 0;
    virtual void increment() = 0;
    void decrement();
    virtual ~Base() = default;
};



#endif //BASE_H
