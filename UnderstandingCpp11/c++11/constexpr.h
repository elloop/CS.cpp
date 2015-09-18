#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(constexpr)

#ifdef _MSC_VER
#else
//---------------------- const expression function ----------------------
// Four condition:
// 1. function body can contain only a return statement(except for use,typedef...)
// 2. must have return value(cannot be void).
// 3. must be defined, before using.
// 4. return statement cannot contains: non-const expression, global data. 
// it must be a const expression.

// example:
constexpr int data() { const int i = 1; return i;} // wrong, too many statements.
constexpr void f() {}							   // wrong, must have return val.

constexpr int cf();
constexpr int c = cf();							   // wrong, cf is not defined.

int globalInt(100);
constexpr int g() { return globalInt; }			   // wrong, global data..

int nonConstFunc() { return 1;}
constexpr int k() { return nonConstFunc(); }	   // wrong, nonConstFunc is not const expression.

const int returnConst { return 11;}
constexpr int p() { return returnConst(); }        // wrong, returnConst is not const expression.

//---------------------- const expression value ----------------------
// 1.
// const int j=1;
// constexpr int j = 1;
// what's the difference?
// const's j, 如果j在全局的名字空间，编译器一定会为它产生数据;
// constexpr's j 编译器不会为它生成数据（除非代码显示地使用了它的地址)。

// 2. user defined const expression data.
// Two rules:
// 1. constexpr constructor must empty body.
// 2. initial list can only use constexpr expression.

struct Data {
	constexpr Data(int y, int m, int d) : year(y), month(m), day(d) {}
	constexpr int year() {return year;}
	constexpr int month() {return month;}
	constexpr int day() {return day;}
private:
	int year;
	int month;
	int day;
};
constexpr Data kBirth(1988, 5, 12);
constexpr int birthMonth = kBirth.month();

//---------------------- use in template ----------------------
template <typename T>
constexpr T makeConstexpr(T t) {
	return t;
}

struct NonConstexpr {
	int i;
	NonConstexpr() {i = 1;}
};

void test() {
	NonConstexpr n1;
	NonConstexpr n2 = makeConstexpr(n1);			// constexpr is ignored, because n1 is not constexpr
	constexpr int i = makeConstexpr(10);			// ok
}

//---------------------- constexpr meta programming ----------------------
constexpr int fib(int n) {
	return (n == 1) ? 1 : ((n == 2) ? 1 : fib(n-1) + fib(n-2));
}

int fibs[] = {
	fib(11), fib(12), fib(20)
};



#endif

NS_END(constexpr)
NS_END(elloop)