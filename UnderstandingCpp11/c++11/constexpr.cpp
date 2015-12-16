#include "constexpr.h"
NS_BEGIN(elloop)
NS_BEGIN(constexpr)

BEGIN_TEST(Constexpr, UseDefinedConstData, @);
#ifdef _MSC_VER
#else
	EXPECT_EQ(6, birthMonth);
#endif
END_TEST;

NS_END(constexpr)
NS_END(elloop)