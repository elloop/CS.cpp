#pragma once

#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(template_test);

class A
{};

class B
{};

template <typename T>
T returnT(T t)
{
    return t;
}

template <>
B returnT<B>(B t)
{
    return t;
}





NS_END(template_test);
NS_END(elloop);
