#include "va_args_test.h"
#include <cstdarg>

NS_BEGIN(elloop);



#include <cstdarg>

int vsum(int count, ...) {

    // 定义一个变长参数类型的指针变量：ap （Argument Pointer）
    va_list ap;

    // 初始化指针变量ap. (传入的第二个参数count，是用来计算参数地址的，count是函数的第一个参数，后边的参数是根据count的地址来计算出来）
    va_start(ap, count);

    int val;
    int sum(0);

    // 遍历变长参数内容，通过ap。
    for (int i=0; i<count; ++i) {
        val = va_arg(ap, int);
        sum += val;
    }

    // 清理工作
    va_end(ap);

    return sum;
}


//---------------------- begin of new test case ----------------------
BEGIN_TEST(GrammarTest, VA_Args, @@);

EXPECT_EQ(0, vsum(0));
EXPECT_EQ(10, vsum(1, 10));
EXPECT_EQ(10, vsum(2, 5, 5));
EXPECT_EQ(10, vsum(3, 2, 3, 5));
EXPECT_EQ(10, vsum(4, 2, 3, 2, 3));
EXPECT_EQ(10, vsum(5, 2, 3, 2, 2, 1));
EXPECT_EQ(10, vsum(10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));

END_TEST;

template <typename T, typename ... Args>
int vprint(const T &t, const Args&... args) {
    int sum(0);
    sum += t;
    sum += vprint(args...);
    return sum;
}

template <typename T>
int vprint(const T &t) {
    return t;
}


template <long ... Args> vsum;

template <long T, long ... Args>
class vsum<T, Args&...> {
public:
    static const T value = t + vsum<Args&...>::value;
};

template <>
class vsum<> {
public:
    static const int value = 0;
};

//template <typename ... Args> vsum;
//
//template <typename T, typename ... Args>
//class vsum<T, Args&...> {
//public:
//    static const T value = t + vsum<Args&...>::value;
//};
//
//template <>
//class vsum<> {
//public:
//    static const int value = 0;
//};

RUN_GTEST(GrammarTest, VPrint, @@);

psln(vprint(1, 2, 3, 4));

END_TEST;

/*
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from GrammarTest
[ RUN      ] GrammarTest.VA_Args
@@@@@@@@@@@@@@@@@@@@ GrammarTest ---> VA_Args @@@@@@@@@@@@@@@@@@@@
[       OK ] GrammarTest.VA_Args (4 ms)
[----------] 1 test from GrammarTest (4 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (4 ms total)
[  PASSED  ] 1 test.
*/

NS_END(elloop);