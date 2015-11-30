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

class ImplicitContructable {
public:
    ImplicitContructable(int x = 0) : x_(x) {
        ++s_constructCount_;
        pln("ImplicitContructable() called");
    }

    ImplicitContructable(ImplicitContructable& other) : x_(other.x_) {
        pln("ImplicitContructable(ImplicitContructable& other) called");
        ++s_constructCount_;
    }

    int x_;
    static int s_constructCount_;
};

NS_END(class_test)
NS_END(elloop);
