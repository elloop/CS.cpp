#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <type_traits>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;

void print(int n1, int n2, int n3)
{
    p(n1); p(" "); p(n2); p(" "); p(n3); cr;
}

template <typename T1, typename T2>
auto add(const T1 & t1, const T2& t2) -> decltype(t1 + t2)
{
    return t1 + t2;
}

double multiply(double d1, double d2)
{
    return d1 * d2;
}

double divide(double d1, double d2)
{
    assert(d2 != 0);
    return d1 / d2;
}


class Foo
{
public:
    void f(int n1, int n2, int n3)
    {
        p(n1); p(" "); p(n2); p(" "); p(n3); cr;
    }
};

RUN_GTEST(FunctorTest, Bind, @);

// prototype of template function bind.
// template <class Fn, class... Args>
// /* unspecified */ bind(Fn&& fn, Args&&... args);

// template <class Ret, class Fn, class... Args>
// /* unspecified */ bind(Fn&& fn, Args&&... args);

pcln("Bind Test");
int i(100);
double d(3.0);
auto result = add(i, d);


auto doublize = bind(multiply, _1, 2.0);
EXPECT_EQ(200.0, doublize(i));

auto double20 = bind(multiply, 2, 10);
EXPECT_EQ(20.0, double20());

double d1 = divide(10, 2);
EXPECT_EQ(5, d1);
auto revertDivide = bind(divide, _2, _1);
double d2 = revertDivide(10, 2);
EXPECT_EQ(1 / 5.0, d2);

auto rounding = bind<int>(divide, _1, _2);
auto i1 = rounding(10, 3);
bool isSameType = is_same<int, decltype(i1)>::value;
EXPECT_TRUE(isSameType);
EXPECT_EQ(3, i1);

//-------------------------------- place holder --------------------------------
auto arg3 = bind(print, _3, _2, _1);
arg3(1, 2, 3);  // 3 2 1
auto arg2 = bind(print, _1, _1, _2);
arg2(1, 2);     // 1 1 2
auto arg1 = bind(print, _1, _1, _1);
arg1(1);        // 1 1 1 
auto arg0 = bind(print, 1, 1, 1);
arg0();         // 1 1 1
arg0(2);        // 1 1 1, 2 is ignored.
arg0(2,2,2);    // 1 1 1, 2 2 2 is ignored.

// try to accept 4 args
auto arg4 = bind(print, _2, _3, _4);
//arg4(1, 2, 3);    // compile error, too few args.可多不可少 in call
arg4(1, 2, 3, 4);   // 2 3 4; 1 is ignored.
arg4(1, 2, 3, 4, 5);    // ok, 5 is ignored.
arg4(1, 2, 3, 4, 5, 6, 7, 8);  // ok, 5~8 are ignored. 可多不可少 in call

// try to accept 5 args
auto arg5 = bind(print, _1, _3, _5);
arg5(1, 2, 3, 4, 5);    // 1 3 5; 2,4 is ingored.

// try to use more than 3 placeholders
auto hold4 = bind(print, _1, _2, _3, _4);   // 个数必须一致 in definition
// error, too many args, caused by too many placeholders in definition of hold4.
//hold4(1, 2, 3, 4);    

// try to use fewer than 3 placeholders.
auto hold2 = bind(print, _1, _2);           // 个数必须一致 in definition
// error, too few args, caused by too few placeholders in definition of hold2.
//hold2(1, 2, 3);

cr; cr;

//-------------------------- bind member function ----------------------
Foo foo;

auto mfarg4 = bind(&Foo::f, _1, _2, _3, _4);
mfarg4(&foo, 10, 20, 30);   // 10 20 30; 
// or use object directly.
mfarg4(foo, 10, 20, 30);    // 10 20 30; 

auto mfarg3 = bind(&Foo::f, _1, _2, _3, 30);
mfarg3(&foo, 10, 20);       // 10 20 30; 

auto mfarg2 = bind(&Foo::f, _1, _2, 20, 30);
mfarg2(&foo, 10);           // 10 20 30; 

auto mfarg1 = bind(&Foo::f, _1, 10, 20, 30);
mfarg1(foo);                // 10 20 30;

auto mfarg0 = bind(&Foo::f, &foo, 10, 20, 30);
mfarg0();                   // 10 20 30

std::function<void(int, int, int)> ff;
ff = bind(&Foo::f, &foo, _1, _2, _3);

//--------------------------------- nested bind--------------------------------
auto lambdaf = [](int x) -> int { return x;};
auto nestedf = bind(print, _1, bind(lambdaf, _1), _2);
nestedf(1, 2);

// work with template function.
auto addby2 = bind(add<double, double>, _1, 2.0);
psln(addby2(10.2));       // 12.2

// TODO : why bind can't work with template function?
//auto addBy2 = bind<double>(add, _1, 2.0); 
// ANSWER: stupid! 
// bind<T> means bind's return value f, will return a value of type T.
// for example:
auto addby2_int = bind<int>(add<double, double>, _1, 2.0);
psln(addby2_int(10.2));     // 12

END_TEST;



NS_END(elloop);