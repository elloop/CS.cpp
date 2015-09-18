#include "constexpr.h"
NS_BEGIN(elloop)
NS_BEGIN(constexpr)

TEST(Constexpr, UseDefinedConstData) {
#ifdef _MSC_VER
#else
	EXPECT_EQ(6, birthMonth);
#endif
}
NS_END(constexpr)
NS_END(elloop)