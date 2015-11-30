#pragma once
#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(temp);


template <long ... Args> class Multiply;

template <long n, long ... Others>
class Multiply<n, Others...> {
public:
    static const long value = n * Multiply<Others...>::value;
};

template <>
class Multiply<> {
public:
    static const long value = 1;
};



NS_END(temp);
NS_END(elloop);