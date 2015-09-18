#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(trailing_return_type)

// review following sum definition in decltype namespace.
// its drawback is that you must call this function with a third param which
// should be exactly the same type of (t1 + t2).
template<typename T1, typename T2>
void sum(const T1 & t1, const T2 & t2, decltype(t1 + t2) & sum) {
	return (t1 + t2);
}


// this won't work, because t1 and t2 (int decltype(t1+t2)) 
// are unknown symbols before parse params list.
template<typename T1, typename T2>
decltype(t1 + t2) sum2(const T1& t1, const T2 & t2) {
	return t1 + t2;
}

template <typename T1, typename T2>
auto sum(const T1 & t1, const T2 & t2) -> decltype(t1 + t2) {
	return (t1 + t2);
}

// this feature can also used with :
// 1. normal function(pointer), function template, function reference definition/declaration.
// 2. member function of struct or class, class template member function and so on.

//---------------------- examples ----------------------
// 1. normal function 
auto foo() -> int {
	return 1;
}

auto foo2() -> void {}


// function pointer
//a complex function definition.
// pf() defines a function, whose 
// return type A is a function ptr pA( pA = B (*pA)() ),
// pA points to a type B, which is still a function ptr ( B = int (*)() ).
int(*(*pf())())() {
	return nullptr;
}

// same with:
auto pf1() -> auto (*)() -> int(*)() {
	return  nullptr;
}

// pf and pf1 are function type, 
// compare with following codes, 
// which define a function pointer type ptr_ptr_func_t.
// ptr_ptr_func_t type is the same type with &pf or &pf1.
typedef int(*(*ptr_ptr_func_t)())();

// tricks:
// 从变量x开始看，先往右看有没有（括号，有，那么x是一个函数定义；
// 否则，右边是）括号，往左看看到*，那么它是一个函数指针定义；


// 2. member function.
class A {
public:
	auto foo() -> int {
		return data_;
	}
private:
	int data_{ 10 };
};

template<typename T>
class IntWrapper {
public:
	IntWrapper(int * ptr);
	IntWrapper(const IntWrapper & other) = delete;
	IntWrapper& operator= (const IntWrapper & other) = delete;

	auto data() -> T {
		assert(ptr_ != nullptr);
		return *ptr_;
	}
	~IntWrapper();

	auto ptr()->const T*;

private:
	T* ptr_;
};

template<typename T>
IntWrapper<T>::IntWrapper(int * ptr) : ptr_(ptr) {
}

template<typename T>
IntWrapper<T>::~IntWrapper() {
	if (ptr_) {
		delete ptr_;
		ptr_ = nullptr;
	}
}

template<typename T>
auto IntWrapper<T>::ptr() -> const T*{
	return ptr_;
}



NS_END(trailing_return_type)
NS_END(elloop)