#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include <initializer_list>
#include <vector>
#include "inc.h"

NS_ELLOOP_BEGIN

class InitializerTest {
public:
    InitializerTest(const std::initializer_list<int>& iv) {
        auto i = iv.begin();
        while (i != iv.end()) {
            data_.push_back(*i);
            ++i;
        }
    }
    InitializerTest& operator[] (const std::initializer_list<int>& indexs) {
        auto i = indexs.begin();
        while (i != indexs.end()) {
            indexs_.push_back(*i++);
        }
        return *this;
    }
    InitializerTest& operator= (int v) {
        for (auto i = indexs_.begin(); i != indexs_.end(); ++i) {
            if (static_cast<std::vector<int>::size_type>(*i)
                >= data_.size()) {
                data_.resize(*i);
            }
            data_[*i - 1] = v;
        }
        return *this;
    }

    const std::vector<int>& data() const {
        return data_;
    }
    const std::vector<int>& indexes() const {
        return indexs_;
    }
    std::vector<int>::size_type size() const {
        return data_.size();
    }
private:
    std::vector<int> indexs_;
    std::vector<int> data_;
};

//--------------------------- type convert test ---------------------------
class ConvertToInt {
public:
    int operator() () {
        return 10;
    }
};

class A {};
class B {};
class CanBeAB {
public:
    // operator () overload.
    A operator() () {
        pln("operator () called!");
        return A();
    }
    // custom convert operator.
    operator A() {
        pln("operator A() called!");
        return A();
    }
    // custom convert operator.
    explicit operator B() {
        pln("operator B() called!");
        return B();
    }
};
void funcA(A a);
void funcB(B b);

NS_ELLOOP_END
