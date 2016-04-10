#pragma once

#include "inc.h"

NS_BEGIN(elloop);

struct Simple
{
    int     x;
    int     y;
};

struct Combo
{
    Simple      sim;
    int         z;
};

namespace from_opengl_test
{
    // in cpp test struct init from opengl-es-2.0-test.    
}

NS_END(elloop);