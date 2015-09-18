#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(decltype_test)

// used for testing typedid.hash_code.
class TypeA {};
class TypeB {};

// testing anonymous struct type.
struct { int a; } a_struct_value;

// testing using decltype in template function.
template <typename T1, typename T2>
void Sum2(T1 & t1, T2 &t2, decltype(t1 + t2) & s) {
	s = t1 + t2;
}

// Notice when using decltype.
// 4-rules: decltype(e)
// 1. 如果e：
//      1) 是不带括号的标记符(id-expression)或者
//      2) 类成员访问表达式
//    那么decltype(e)的类型就是e的类型。
// 2. 否则，如果e是一个将亡值(xvalue), 类型为T，那么decltype(e)类型为T&&.
// 3. 否则，如果e是一个左值, 那么decltype(e)为T&.
// 4. 否则，其他情况，decltype(e)为T.
// see TEST(Decltype, FourRulesForUsingDecltype) in decltype.cpp.

NS_END(decltype_test)
NS_END(elloop)