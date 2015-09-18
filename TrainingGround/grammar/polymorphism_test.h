#if defined(_MSC_VER)
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>

NS_BEGIN(elloop);


// case 1:
//struct A{
//  void fun1() { std::cout << "1"; }
//};
//
//struct B :public A {
//  void fun2(A *a) { std::cout << "2"; }
//};
//
//int main() {
//  A a;
//  B *b = static_cast<B*>(&a);
//  b->fun2(&a);
//  std::cout << 3 << std::endl;
//}
// output: 23



// case 2.
//struct A{
//  void fun1() { std::cout << "1"; }
//};
//struct B :public A {
//  void fun2(A *a) { std::cout << "2"; }
//};
//void main() {
//  A a;
//  B *b = dynamic_cast<B*>(&a);
//  b->fun2(&a);
//  std::cout << 3 << std::endl;
//}
// compile error: dynamic_cast must use with virtual.


//case 3.
//struct A{
//  virtual void fun1() { std::cout << "1"; }
//};
//struct B :public A {
//  virtual void fun2(A *a) { std::cout << "2"; }
//};
//void main() {
//  A a;
//  B *b = static_cast<B*>(&a);
//  b->fun2(&a);
//  std::cout << 3 << std::endl;
//}
// runtime error: can't find fun2 in vtbl of class object a.


// case 4.
//struct A{
//  virtual void fun1() { std::cout << "1"; }
//};
//struct B :public A {
//  virtual void fun2(A *a) { std::cout << "2"; }
//};
//void main() {
//  A a;
//  B *b = dynamic_cast<B*>(&a);
//  b->fun2(&a);
//  std::cout << 3 << std::endl;
//}
// runtime error: a downcast to b will fail. b is nullptr.


NS_END(elloop);
