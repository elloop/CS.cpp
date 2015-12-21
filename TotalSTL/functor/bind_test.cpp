#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <algorithm>
#include <iterator>
#include <memory>       // shared_ptr.
#include <type_traits>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;

/*

prototype of template function bind.

template <class Fn, class... Args>
unspecified bind(Fn&& fn, Args&&... args);

template <class Ret, class Fn, class... Args>
unspecified bind(Fn&& fn, Args&&... args);

*/


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

double divide(double d1, int n)
{
    assert(n != 0);
    return d1 / n;
}

int ret4()
{
    pln("ret4() called");
    return 4;
}

class Foo
{
public:
    void f(int n1, int n2, int n3)
    {
        p(n1); p(" "); p(n2); p(" "); p(n3); cr;
    }

    void print()
    {
        psln(a_);
    }

    int a_{ 100 };
};

class Movable
{
public:
    Movable(int size = 1000000) : size_(size)
    {
        hugeMem_ = new int[size_];
    }

    ~Movable()
    {
        if (hugeMem_)
        {
            delete hugeMem_;
        }
    }

    Movable(Movable&& moved) : hugeMem_(moved.hugeMem_)
    {
        pln("Movable move ctr called");
        moved.hugeMem_ = nullptr;
    }

    int     *hugeMem_;
    int     size_;
};

Movable returnMovable()
{
    Movable m;
    LOGD("in %s, m.hugeMem_ is : %x\n", __FUNCTION__, m.hugeMem_);
    return m;
}

void useMoveable(Movable m1, Movable m2)
{
    psln(m1.hugeMem_);
    psln(m2.hugeMem_);
}


//----------------------------- BindNormalFunction ------------------------------
BEGIN_TEST(FunctorTest, BindNormalFunction, @);

auto emptyArg = bind(multiply, 1, 2);
EXPECT_EQ(2, emptyArg());

auto need2arg = bind(multiply, _1, _2);
EXPECT_EQ(2, need2arg(1, 2));
EXPECT_EQ(2, need2arg(1, 2, ret4()));

auto same = bind(multiply, _1, _2);
EXPECT_EQ(200.0, same(2, 100));

auto doublize = bind(multiply, _1, 2.0);
EXPECT_EQ(200.0, doublize(100));

auto ret_20 = bind(multiply, 2, 10);
EXPECT_EQ(20.0, ret_20());

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

END_TEST;




//----------------------------- UsePlaceholders -----------------------------
BEGIN_TEST(FunctorTest, UsePlaceholders, @);
auto arg3 = bind(print, _3, _2, _1);
arg3(1, 2, 3);  // 3 2 1
auto arg2 = bind(print, _1, _1, _2);
arg2(1, 2);     // 1 1 2
auto arg1 = bind(print, _1, _1, _1);
arg1(1);        // 1 1 1 
auto arg0 = bind(print, 1, 1, 1);
arg0();         // 1 1 1
arg0(2);        // 1 1 1, 2 is ignored.
arg0(2, 2, 2);    // 1 1 1, 2 2 2 is ignored.

// try to accept 4 args
auto arg4 = bind(print, _2, _3, _4);
//arg4(1, 2, 3);                // compile error, too few args.可多不可少 in call
arg4(1, 2, 3, 4);               // 2 3 4; 1 is ignored.
arg4(1, 2, 3, 4, 5);            // ok, 5 is ignored.
arg4(1, 2, 3, 4, 5, 6, 7, 8);   // ok, 5~8 are ignored. 可多不可少 in call

// try to accept 5 args
auto arg5 = bind(print, _1, _3, _5);
arg5(1, 2, 3, 4, 5);    // 1 3 5; 2,4 is ingored.


/*
if fn() need N args, then the number of placeholders S, and the number of normal args
V, should satisfy N == S + V.
*/
// try to use more than 3 placeholders
auto hold4 = bind(print, _1, _2, _3, _4);   // 个数必须一致 in bind
// error, too many args, caused by too many placeholders in definition of hold4.
//hold4(1, 2, 3, 4);    

// try to use fewer than 3 placeholders.
auto hold2 = bind(print, _1, _2);           // 个数必须一致 in definition
// error, too few args, caused by too few placeholders in definition of hold2.
//hold2(1, 2, 3);

//auto hold_100 = bind(print, _100, _1, _2);    // max placeholders is _20 (VC++)
END_TEST;




//----------------------------- BindMemberFunction -----------------------------
BEGIN_TEST(FunctorTest, BindMemberFunction, @);
Foo foo;
Foo &foo_ref = foo;

auto mfarg4 = bind(&Foo::f, _1, _2, _3, _4);
// or use object directly.
mfarg4(foo, 10, 20, 30);    // 10 20 30; 
// use object pointer.
mfarg4(&foo, 10, 20, 30);   // 10 20 30; 
// use object ref.
mfarg4(foo_ref, 10, 20, 30);    // 10 20 30; 

auto mfarg3 = bind(&Foo::f, _1, _2, _3, 30);
mfarg3(&foo, 10, 20);       // 10 20 30; 

auto mfarg2 = bind(&Foo::f, _1, _2, 20, 30);
mfarg2(&foo, 10);           // 10 20 30; 

auto mfarg1 = bind(&Foo::f, _1, 10, 20, 30);
mfarg1(foo);                // 10 20 30;

auto mfarg0 = bind(&Foo::f, foo, 10, 20, 30);
mfarg0();                   // 10 20 30

auto mfarg01 = bind(&Foo::f, &foo, 10, 20, 30);
mfarg01();                  // 10 20 30
auto mfarg02 = bind(&Foo::f, foo_ref, 10, 20, 30);
mfarg02();                      // 10 20 30

// assign a mem_func to std::function.
std::function<void(int, int, int)> normal_func;
normal_func = bind(&Foo::f, foo, _1, _2, _3);
normal_func(10, 20, 30);        // 10 20 30

//------------------------------ bind member var ----------------------------
auto bindMv = bind(&Foo::a_, _1);
psln(bindMv(foo));             // bindMv(foo) = 100
//psln(bindMv(&foo));          // bindMv(foo) = 100
psln(bindMv(foo_ref));         // bindMv(foo) = 100

END_TEST;





//--------------------------- SubexpressionOfBind ---------------------------
BEGIN_TEST(FunctorTest, SubexpressionOfBind, @);

auto addby1 = [](int x) -> int
{
    cout << "addby1() called" << endl;
    return (x + 1);
};

auto nestedF = bind(print, _1, bind(addby1, _1), _2);
nestedF(1, 3);                 // addby1() called<cr> 1 2 3

END_TEST;




//-------------------------- BindTemplateFunction ---------------------------
BEGIN_TEST(FunctorTest, BindTemplateFunction, @);

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




//--------------------------------- test ref ---------------------------------
BEGIN_TEST(FunctorTest, ReferenceWrapperBind, @);

int x(10);
auto bindRef = bind(print, 1, std::cref(x), x);
bindRef();                // 1 10 10;
x = 100;
bindRef();                // 1 100 10;

END_TEST;




//-------------------------------- bind movable obj --------------------------------
BEGIN_TEST(FunctorTest, BindMovable, @);

//Movable movable;
//psln(movable.hugeMem_);
//auto bindMoved = bind(useMoveable, _1, _2);
//bindMoved(returnMovable(), returnMovable());
//psln(movable.hugeMem_);

END_TEST;




//----------------------------- Bind Predefined Functors -----------------------------
BEGIN_TEST(FunctorTest, BindPredefinedFunctors, @);

// all predefined functors:
// negate, plus, minus, multiplies, divides, modulus, equal_to, 
// not_equal_to, less, greater, less_equal, greater_equal,
// logical_not, logical_and, logical_or, bit_and, bit_or, bit_xor

auto tenTimes = bind(multiplies<int>(), _1, 10);
EXPECT_EQ(100, tenTimes(10));
EXPECT_EQ(200, tenTimes(20));
EXPECT_EQ(300, tenTimes(30));

vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8 };
// nested bind. output v[i] if 10*v[i] > 50.
copy_if(v.begin(), v.end(),
    ostream_iterator<int>(cout, ", "),
    bind(greater<int>(),
        bind(multiplies<int>(), _1, 10),
        50));                               // 6,7,8,
cr;

END_TEST;




//----------------------------- Bind smart pointer -----------------------------
RUN_GTEST(FunctorTest, BindSmartPointer, @);

struct Temp 
{
    Temp(int i=0) : i_(i) {}
    void print() { pln(i_); }
    int i_;
};

vector<shared_ptr<Temp>> vs =
{
    shared_ptr<Temp>(new Temp(1)),
    shared_ptr<Temp>(new Temp(2)),
    shared_ptr<Temp>(new Temp(3)),
};

for_each(vs.begin(), vs.end(), bind(&Temp::print, _1));  // 1<cr>2<cr>3<cr>

bind(&Temp::print, vs[0])();        // 1
bind(&Temp::print, vs[1])();        // 2
bind(&Temp::print, vs[2])();        // 3

END_TEST;






NS_END(elloop);