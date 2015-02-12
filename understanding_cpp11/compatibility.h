_Pragma("once")

#include "inc.h"
#include "base_test.h"

NS_ELLOOP_BEGIN

#if __cplusplus < 201103L
#error "should use c++11 complier."
#endif

static_assert(sizeof(int) == 4, "sizeof int should be 4 bytes.");

class Compatibility : public BaseTest {
    public:
        // using BaseTest::BaseTest(10);
        Compatibility * run() override;
};

NS_ELLOOP_END
