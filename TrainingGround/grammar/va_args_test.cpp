#include "va_args_test.h"
#include <cstdarg>

#include <string>

NS_BEGIN(elloop);

int vsum(int count, ...) {
    va_list ap;
    va_start(ap, count);

    int val(0);
    int sum(0);
    for (int i=0; i<count; ++i) {
        sum += va_arg(ap, int);
    }
    va_end(ap);
    return sum;
}

// ------------------ begin of new test case ------------------
BEGIN_TEST(GrammarTest, VA_Args, @@);

// ------------------ function vsum using va_list ------------------
EXPECT_EQ(0, vsum(0));
EXPECT_EQ(10, vsum(1, 10));
EXPECT_EQ(10, vsum(2, 5, 5));
EXPECT_EQ(10, vsum(3, 2, 3, 5));
EXPECT_EQ(10, vsum(4, 2, 3, 2, 3));
EXPECT_EQ(10, vsum(5, 2, 3, 2, 2, 1));
EXPECT_EQ(10, vsum(10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));

// ------------------ template function vsum1 ------------------
EXPECT_EQ(0, vsum1(0));
EXPECT_EQ(10, vsum1(5, 5));
EXPECT_EQ(10, vsum1(3, 3, 3, 1));
EXPECT_EQ(10, vsum1(2, 2, 2, 2, 2));
EXPECT_EQ(10, vsum1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
EXPECT_EQ(6, vsum1(1, 2.5, 3));
EXPECT_EQ(6.5, vsum1(1.5, 2, 3));

std::string t1 = typeid(decltype(vsum1(1, 2.5, 3))).name();
EXPECT_STREQ("int", t1.c_str());

std::string t2 = typeid( decltype( vsum1(1.5, 2, 3) ) ).name();
EXPECT_STREQ("double", t2.c_str());

// ------------------ template class vsum2 ------------------
long s = vsum2<>::value;                         EXPECT_EQ(0, s);

s = vsum2<5, 5>::value;                          EXPECT_EQ(10, s);

s = vsum2<5, 2, 3>::value;                       EXPECT_EQ(10, s);

s = vsum2<3, 3, 1, 3>::value;                    EXPECT_EQ(10, s);

s = vsum2<1, 1, 1, 1, 1, 1, 1, 1, 1, 1>::value;  EXPECT_EQ(10, s);


long f = vsum2<>()();                            EXPECT_EQ(0, f);

f = vsum2<1>()();                                EXPECT_EQ(1, f);

END_TEST;




NS_END(elloop);