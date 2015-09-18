#pragma once

#include "inc.h"

NS_BEGIN(elloop);

struct Simple {
    int     x;
    int     y;
};

struct Combo {
    Simple      sim;
    int         z;
};

NS_END(elloop);