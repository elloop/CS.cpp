#include "auto.h"
#include "gtest/gtest.h"

NS_ELLOOP_BEGIN
TEST(Auto, Advantage) {
	//int a(1), b(2);
	//EXPECT_EQ(2, Max(a, b));
}

TEST(Auto, UsingAuto) {
	auto x(1), y(2);

	// error: should be same type.
	//auto i(1), j(1.1);  

	struct t {
		// error.
		//auto i = 10;
	};

	// error.
	//std::vector<auto> va;

	// error.
	//void f(auto i = 1);
}
NS_ELLOOP_END