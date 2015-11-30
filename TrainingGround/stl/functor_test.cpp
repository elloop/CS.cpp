#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <type_traits>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;

template <typename T1, typename T2>
auto add(const T1 & t1, const T2& t2) -> decltype(t1 + t2) {
	return t1 + t2;
}

double multiply(double d1, double d2) {
	return d1 * d2;
}

double divide(double d1, double d2) {
	assert(d2 != 0);
	return d1 / d2;
}

BEGIN_TEST(FunctorTest, Bind, @)
	pcln("Bind Test");
	int i(100);
	double d(3.0);
	auto result = add(i, d);

	// todo : why bind can't work with template function?
	//auto addBy2 = bind<double>(add, _2, 2.0);

	auto doublize = bind(multiply, _1, 2.0);
	EXPECT_EQ(200.0, doublize(i));

	auto double20 = bind(multiply, 2, 10);
	EXPECT_EQ(20.0, double20());

	auto revertDivide = bind(divide, _2, _1);
	double d1 = divide(10, 2);
	EXPECT_EQ(5, d1);
	double d2 = revertDivide(10, 2);
	EXPECT_EQ(1 / 5.0, d2);

	auto rounding = bind<int>(divide, _1, _2);
	auto i1 = rounding(10, 3);
	bool isSameType = is_same<int, decltype(i1)>::value;
	EXPECT_TRUE(isSameType);
	EXPECT_EQ(3, i1);
END_TEST


NS_END(elloop);