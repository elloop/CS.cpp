#include "trailing_return_type.h"

NS_BEGIN(elloop)
NS_BEGIN(trailing_return_type)

TEST(TrailingReturnType, UsedInTemplate) {
	int i = 10;
	double d = 1.11;
	auto result = sum(i, d);

	EXPECT_EQ(typeid(result).hash_code(), typeid(double).hash_code());
	// or
	bool same = std::is_same<double, decltype(result)>::value;
	EXPECT_TRUE(same);
}

TEST(TrailingReturnType, UsefulTest) {
    /*
    int( *(*pf())() )() {
        return nullptr;
    }
    
    auto pf1() -> auto (*)() -> int(*)() {
        return  nullptr;
    }

	typedef int( *(*ptr_ptr_func_t)() )();
    */

	bool same = std::is_same<decltype(pf), decltype(pf1)>::value;
	EXPECT_TRUE(same);

    same = std::is_same<ptr_ptr_func_t, decltype(pf())>::value;
    EXPECT_TRUE( same );

	// member function of class.
	A a;
	EXPECT_EQ(10, a.foo());

	// used int class template member function.
	IntWrapper<int> q(new int(1000));
	EXPECT_EQ(1000, q.data());
}
NS_END(trailing_return_type)
NS_END(elloop)