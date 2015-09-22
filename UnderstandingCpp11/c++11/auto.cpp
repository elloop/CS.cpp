#include "auto.h"
#include "gtest/gtest.h"

NS_ELLOOP_BEGIN
TEST(Auto, Advantage) {
	//int a(1), b(2);
	//EXPECT_EQ(2, Max(a, b));
}




BEGIN_TEST(Auto, AutoLimited)

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

END_TEST
	



int globalVar(0);

int& returnGlobalRef() {
    return globalVar;
}

BEGIN_TEST(Auto, AutoAndReference)

int val     = 10;
int& ref1   = val;

auto & ref     = val;       // ref      is int&.
auto  maybeRef = val;       // maybeRef is int.
//auto  maybeRef = 10;      // not affect the result.

//auto & ref      = returnGlobalRef();    // ref      is int&.
//auto  maybeRef  = returnGlobalRef();    // maybeRef is int.


// type of ref and maybeRef depend on whether auto followed by a "&", not depend on rightside of "=".

bool isSame(false);

isSame = std::is_same<decltype(maybeRef), int&>::value; EXPECT_FALSE(isSame);
isSame = std::is_same<decltype(maybeRef), int>::value;  EXPECT_TRUE(isSame);

isSame = std::is_same<decltype(ref), int&>::value;  EXPECT_TRUE(isSame);
isSame = std::is_same<decltype(ref), int>::value;   EXPECT_FALSE(isSame);

// test if ref is really a reference of val.
ref = 100;
EXPECT_EQ(100, val);

maybeRef = 11;
EXPECT_NE(11, val);

// a strange thing is that both ref and maybeRef output "int" for their typeid().name().
psln(typeid(ref).name());           // int
psln(typeid(maybeRef).name());      // int

// conclusion: reference characteristic will be thrown(ignored) by auto.

END_TEST


BEGIN_TEST(Auto, AutoAndPointer)

int val(10);
int* ptr = &val;

auto * autoPtr  = ptr;
auto maybePtr   = ptr;

bool isSame(false);
isSame = std::is_same<decltype(autoPtr), int*>::value; EXPECT_TRUE(isSame);
isSame = std::is_same<decltype(autoPtr), int>::value;  EXPECT_FALSE(isSame);

isSame = std::is_same<decltype(maybePtr), int*>::value; EXPECT_TRUE(isSame);
isSame = std::is_same<decltype(maybePtr), int>::value;  EXPECT_FALSE(isSame);

*autoPtr = 100;
EXPECT_EQ(100, val);

*maybePtr = 11;
EXPECT_EQ(11, val);


psln(typeid(autoPtr).name());       // int*
psln(typeid(maybePtr).name());      // int*

// conclusion: pointer characteristic will be retain by auto.


END_TEST



BEGIN_TEST(Auto, AutoAndConst);

int val(10);
const int cval(11);

const auto autocVal = cval;
auto maybecVal      = cval;

bool isSame(false);
isSame = std::is_same<decltype(autocVal), const int>::value;    EXPECT_TRUE(isSame);
isSame = std::is_same<decltype(autocVal), int>::value;          EXPECT_FALSE(isSame);

//autocVal = 11;        // error

isSame = std::is_same<decltype(maybecVal), int>::value;         EXPECT_TRUE(isSame);
isSame = std::is_same<decltype(maybecVal), const int>::value;   EXPECT_FALSE(isSame);

maybecVal = 11;         // ok

psln(typeid(autocVal).name());       // int
psln(typeid(maybecVal).name());      // int

// conclusion: const will be ignored by auto.

END_TEST;



BEGIN_TEST(Auto, AutoAndConstRefAndPtr);

int val(10);
const int& cvalRef = val;

auto maybecvalRef = cvalRef;
bool isSame(false);
isSame = std::is_same<decltype(maybecvalRef), int>::value;          EXPECT_TRUE(isSame);
isSame = std::is_same<decltype(maybecvalRef), const int>::value;    EXPECT_FALSE(isSame);
isSame = std::is_same<decltype(maybecvalRef), int&>::value;         EXPECT_FALSE(isSame);
isSame = std::is_same<decltype(maybecvalRef), const int&>::value;   EXPECT_FALSE(isSame);
psln(typeid(maybecvalRef).name());       // int

const int* cvalPtr  = &val;
auto maybecvalPtr   = cvalPtr;

// 前提：我们已经知道指针是会被代入到auto里面的，因此不需要和int和const int两种类型对比
isSame = std::is_same<decltype(maybecvalPtr), int*>::value;          EXPECT_FALSE(isSame);
isSame = std::is_same<decltype(maybecvalPtr), const int*>::value;    EXPECT_TRUE(isSame);
psln(typeid(maybecvalPtr).name());       // int const *

// conclusion: with reference, const and & will both be ignored.
// with pointer, const and * both will be considered.

END_TEST;

NS_ELLOOP_END