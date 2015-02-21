_Pragma("once")

#include "inc.h"
#include "base_test.h"

NS_ELLOOP_BEGIN

class ThreadTest : public BaseTest {
  public:
    ThreadTest * run() override;
    void testWithCpp11();
    void testWithPthread();
    void testAtomic();
};

NS_ELLOOP_END
