#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <algorithm>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;



class Foo
{
public:
    void print() { pln(a_); }

    void print2(int i) 
    {
        pln(a_);
        pln(i);
    }

    int a_{ 100 };
};


//----------------------- c++98 mem_fun and c++11 mem_fn -----------------------
BEGIN_TEST(FunctorTest, Mem_FunTest, @);

// 1. mem_fun is for a pointer to an obj.
vector<Foo*> fpv;
fpv.push_back(new Foo());
fpv.push_back(new Foo());
fpv.push_back(new Foo());
fpv.push_back(new Foo());

for_each(fpv.begin(), fpv.end(), mem_fun(&Foo::print));
cr;
//for_each(fpv.begin(), fpv.end(), mem_fun_ref(&Foo::print)); // error.

for_each(fpv.begin(), fpv.end(), bind(&Foo::print, _1));    // also can use bind
cr;

// mem_fun doesn't work if member function take extra params.
//for_each(fpv.begin(), fpv.end(), mem_fun(&Foo::print2, 10));
for_each(fpv.begin(), fpv.end(), bind(&Foo::print2, _1, 10)); // must use bind


// 2. mem_fun_ref is for obj.
vector<Foo> fv;
fv.push_back(Foo());
fv.push_back(Foo());
fv.push_back(Foo());
fv.push_back(Foo());

for_each(fv.begin(), fv.end(), mem_fun_ref(&Foo::print));
cr;

//for_each(fv.begin(), fv.end(), mem_fun(&Foo::print));

for_each(fv.begin(), fv.end(), bind(&Foo::print, _1));      // also can use bind
cr;

// mem_fun doesn't work if member function take extra params.
//for_each(fv.begin(), fv.end(), mem_fun_ref(&Foo::print2, 10));
for_each(fv.begin(), fv.end(), bind(&Foo::print2, _1, 10)); // must use bind


// 3. mem_fn work for obj, ref to obj and ptr to obj.
for_each(fpv.begin(),   fpv.end(),  mem_fn(&Foo::print));       // ptr
for_each(fv.begin(), fv.end(), mem_fn(&Foo::print));            // obj

//for_each(fv.begin(), fv.end(), mem_fn(&Foo::print2, 10));
for_each(fv.begin(), fv.end(), bind(&Foo::print2, _1, 10)); //must use bind

Foo foo;
Foo &foo_ref = foo;
mem_fn(&Foo::print)(foo_ref);                                   // ref


// clear pointers.
for_each(fpv.begin(), fpv.end(), [&](Foo* foo)
{
    delete foo;
    foo = nullptr;
});

END_TEST;




NS_END(elloop);