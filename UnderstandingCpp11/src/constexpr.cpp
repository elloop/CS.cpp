#include "constexpr.h"
NS_BEGIN(elloop)
NS_BEGIN(constexpr_test)

BEGIN_TEST(Constexpr, UseDefinedConstData, @);
#ifdef _MSC_VER
#else
	EXPECT_EQ(6, birthMonth);
#endif
END_TEST;

NS_END(constexpr_test)
NS_END(elloop)
