#pragma once

#include "inc.h"
#include <functional>
#include <ostream>
NS_BEGIN(elloop);
NS_BEGIN(set_test);

class Elem
{
public:
    Elem(int weight = 0) : weight_(weight) {}
    int     weight_;
};

class ElemWithLess
{
public:
    ElemWithLess(int weight = 0) : weight_(weight) {}

    bool operator < (const ElemWithLess &other) const
    {
        return weight_ < other.weight_;
    }

    int     weight_;
};

// need one class type parameter at least.
//bool operator < (const Elem *e1, const Elem *e2);


NS_END(set_test);
NS_END(elloop);


template <>
class std::less<elloop::set_test::ElemWithLess*>
{
public:
    bool operator () (
        const elloop::set_test::ElemWithLess* e1, 
        const elloop::set_test::ElemWithLess* e2)
    {
        return ( (*e1) < (*e2) );
    }
};
