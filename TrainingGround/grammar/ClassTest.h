#pragma once

#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(class_test)

class A {
public:
    A() : _a(new int(10)) { }

    ~A() { 
        delete _a;
        _a = nullptr; 
    }

    int*    a() const { return _a; }

private:
    int*    _a;
};

NS_END(class_test)
NS_END(elloop);
