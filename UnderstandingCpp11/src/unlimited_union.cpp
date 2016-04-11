#include "unlimited_union.h"
#include "gtest/gtest.h"
#include <type_traits>

NS_ELLOOP_BEGIN

USING_NS_STD;

namespace union_test {

BEGIN_TEST(UnlimitedUnion, Pod, @);
    EXPECT_TRUE(is_pod<Pod>::value);
    EXPECT_FALSE(is_pod<NonPod>::value);
    ContainNonPod cnp;
    cnp.id = 10;
    strcpy(cnp.name, "hello");
    psln(cnp.name);
END_TEST;

}

NS_ELLOOP_END