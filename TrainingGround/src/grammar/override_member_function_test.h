#pragma once

#include "inc.h"

NS_BEGIN(elloop);
NS_BEGIN(override_test);

class Super {
public:
    virtual void addChild(int i, int j = 0);
};

class D1 : public Super {
public:

private:
    void addChild(int i, int j /* = 0 */) override {}
};

NS_END(override_test);
NS_END(elloop);
