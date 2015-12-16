#include "using_vs_typedef.h"
#include "gtest/gtest.h"

NS_ELLOOP_BEGIN

USING_NS_STD;
BEGIN_TEST(Using, TemplateUsing, @);
	IntMap<std::string> age_map {
		{ "Tom", 11 },
		{ "Jerry", 20 },
		{ "David", 30 }
	};
	bool same = std::is_same < decltype(age_map)
		, std::map < std::string, int >> ::value;
	EXPECT_TRUE(same);
END_TEST;

NS_ELLOOP_END