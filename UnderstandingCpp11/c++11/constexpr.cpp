#include "constexpr.h"
NS_BEGIN(elloop)
NS_BEGIN(constexpression)

BEGIN_TEST(Constexpr, UseDefinedConstData, @);
#ifdef _MSC_VER
#else
	EXPECT_EQ(6, birthMonth);
#endif
END_TEST;

NS_END(constexpression)
NS_END(elloop)