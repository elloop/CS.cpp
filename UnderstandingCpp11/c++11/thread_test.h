#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include "inc.h"
#include "messi.h"

NS_ELLOOP_BEGIN

class ThreadTest : public Messi {
  public:
    ThreadTest * run() override;
    void testWithCpp11();
    void testWithPthread();
    void testAtomic();
};

NS_ELLOOP_END
