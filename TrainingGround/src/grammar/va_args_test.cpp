#include "va_args_test.h"
#include <cstdarg>

#include <string>

NS_BEGIN(elloop);

void passStr(int count, ...) {
    va_list varg;
    va_start(varg, count);

    for (int i=0; i<count; ++i) {
        char* str = va_arg(varg, char*);
        psln(str);
        psln(strlen(str));
    }

    va_end(varg);
}

void passPtrInVargs(int count, ...) {
    va_list varg;

    va_start(varg, count);

    for (int i=0; i<count; ++i) {
        *va_arg(varg, int*) = 100;
    }

    va_end(varg);
}

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
RUN_GTEST(GrammarTest, VA_Args, @@);

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
// EXPECT_STREQ("int", t1.c_str());     // use this with visual c++ compiler.
EXPECT_STREQ("i", t1.c_str());          // use this with clang++.

std::string t2 = typeid( decltype( vsum1(1.5, 2, 3) ) ).name();
// EXPECT_STREQ("double", t2.c_str());  // use this with visual c++ compiler.
EXPECT_STREQ("d", t2.c_str());          // use this with clang++.

// ------------------ template class vsum2 ------------------
long s = vsum2<>::value;                         EXPECT_EQ(0, s);

s = vsum2<5, 5>::value;                          EXPECT_EQ(10, s);

s = vsum2<5, 2, 3>::value;                       EXPECT_EQ(10, s);

s = vsum2<3, 3, 1, 3>::value;                    EXPECT_EQ(10, s);

s = vsum2<1, 1, 1, 1, 1, 1, 1, 1, 1, 1>::value;  EXPECT_EQ(10, s);


long f = vsum2<>()();                            EXPECT_EQ(0, f);

f = vsum2<1>()();                                EXPECT_EQ(1, f);


// ========================= test passing ptr with vargs. ==========================
int x(0);
int y(0);
passPtrInVargs(2, &x, &y);
EXPECT_EQ(100, x);
EXPECT_EQ(100, y);

// ========================= test passing string with vargs. ==========================
passStr(3, "hel", "hello\0hello", "");

END_TEST;




NS_END(elloop);
