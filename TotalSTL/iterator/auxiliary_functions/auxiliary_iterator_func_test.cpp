#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;




//-----------------------  Advance  ----------------------
RUN_GTEST(AuxiliaryIterFuncTest, Advance, @);

array<int, 5> a = {1, 2, 3, 4, 5};
printContainer(a, "a: ");

auto iter = a.begin();
EXPECT_EQ(1, *iter);

advance(iter, 1);       // iter is changed.
EXPECT_EQ(2, *iter);

advance(iter, 2);
EXPECT_EQ(4, *iter);

advance(iter, -1);      // go backward 1.
EXPECT_EQ(3, *iter);

advance(iter, -2);      // go backward 2.
EXPECT_EQ(1, *iter);


iter = a.begin();
pln("advance pass the end()");
//advance(iter, 100);     // undefined behaviour.
//advance(iter, -100);     // undefined behaviour.

END_TEST;



//-----------------------  next  ----------------------
// next(pos, n) calls advance(pos, n) for an internal temporary object.
RUN_GTEST(AuxiliaryIterFuncTest, Next, @);

array<int, 5> a = { 1, 2, 3, 4, 5 };
printContainer(a, "a: ");

auto iter = a.begin();
EXPECT_EQ(1, *iter);

auto pos2 = next(iter, 1);                  // iter is not changed.
EXPECT_EQ(1, *iter);
EXPECT_EQ(2, *pos2);

auto pos3 = next(pos2);                     // default n = 1
EXPECT_EQ(2, *pos2);
EXPECT_EQ(3, *pos3);

auto pos5 = next(iter, 4);                  // iter + 4
EXPECT_EQ(5, *pos5);

auto pos4 = next(pos5, -1);
EXPECT_EQ(4, *pos4);

auto pos1 = next(pos5, -4);
EXPECT_EQ(1, *pos1);

//auto posPassEnd = next(iter, 100);          // error, undefined behaviour.
//auto posBeforeBegin = next(iter, -100);     // error, undefined behaviour.

END_TEST;




//-----------------------  prev ----------------------
// prev(pos, n) calls advance(pos, -n) for an internal temporary object.
RUN_GTEST(AuxiliaryIterFuncTest, Prev, @);

array<int, 5> a = { 1, 2, 3, 4, 5 };
printContainer(a, "a: ");

auto last = prev(a.end());              // call prev with end() is ok.
EXPECT_EQ(5, *last);

auto last2 = prev(a.end(), 2);          // call prev with end() is ok.
EXPECT_EQ(4, *last2);

auto iter = a.begin();                  
auto pos2 = prev(iter, -1);             // move forward use prev.
EXPECT_EQ(2, *pos2);

//auto posBeforeBegin = prev(a.begin(), 1);    // error: undefined behaviour.

END_TEST;




//-----------------------  distance ----------------------
RUN_GTEST(AuxiliaryIterFuncTest, Distance, @);

array<int, 5> a = { 1, 2, 3, 4, 5 };
printContainer(a, "a: ");

auto pos2 = find(a.begin(), a.end(), 2);
auto pos5 = find(a.begin(), a.end(), 5);

//array<int, 5>::difference_type dis = distance(pos2, pos5);

auto dis = distance(pos2, pos5);
psln(dis);                              // dis = 3
EXPECT_EQ(5 - 2, dis);

auto negativeDis = distance(pos5, pos2);
psln(negativeDis);                      // negativeDis = -3
EXPECT_EQ(2 - 5, negativeDis);

END_TEST;



//-----------------------  iter_swap ----------------------
RUN_GTEST(AuxiliaryIterFuncTest, Iter_swap, @);

array<int, 5> a = { 1, 2, 3, 4, 5 };
printContainer(a, "a: ");               // 1 2 3

iter_swap(a.begin(), next(a.begin()));
printContainer(a, "a: ");               // 2 1 3

list<int> l = { 10, 11, 12};
printContainer(l, "l: ");

iter_swap(a.begin(), l.begin());
printContainer(a, "after swap, a: ");   // 10 1 3
printContainer(l, "after swap, l: ");   // 2 11 12

END_TEST;



NS_END(elloop);