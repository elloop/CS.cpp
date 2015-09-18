#ifdef _MSC_VER
#pragma once
#else
_Pragma( "once" )
#endif
#include "inc.h"

NS_BEGIN( elloop )
NS_BEGIN( variadic_template )

// va_arg function in old c++.
// drawback: must specify data type in va_arg.(e.g. va_arg(args, int)).
// i.e. va_arg do not know the type info of the args.
int sum( int count, ... );

// VARIADIC TEMPLATE solve this problem.

// 1. variadic template class
// template <typename...args> class Foo;

// 2. variadic template function
// template <typename ... T> void foo(T ... args);
// restriction: variadic args must be the last param in foo().

// CONCEPTS: unpack, pack expansion.
// two kinds of pack expansion: <Args...>, <Args>... .
// e.g. 
/*
// use <Args...>
template <typename ... Args> class Bar;
template <typename ... Args>
class Foo: private Bar<Args...> {};

if Args == X, Y
class Foo will be:
class Foo : private Bar<X, Y> {}

// use <Args>...
template <typename T> class Bar1;
template <typename ... Args>
class Foo1 : private Bar1<Args>... {};

if Args == X, Y;
class Foo1 will be :
class Foo1 : private Bar1<X>, private Bar1<Y> {}

*/

// 7 PLACES where unpack can happen.
// 1. expression.
// 2. initializer_list
// 3. base class description list.
// 4. class members initial list.
// 5. template params list.
// 6. attribute list.
// 7. lambda's capture list.

//--------------------------- begin test ---------------------------

// 1. define a Tuple use type template.

// declaration.
template <typename ... Args> class Tuple;

// partial specialization
template <typename First, typename ... Others>
class Tuple<First, Others...> : private Tuple<Others...> {
public:
    First first;
};

// end of recursive specialization.
template <> class Tuple<> {};
//------------------------------------------------------

//----------------------- nontype template (非类型模板) -----------------------
// 2. Multiply, using template meta programming.
template <long ... Args> class Multiply;

template <long n, long ... Others>
class Multiply<n, Others...> {
public:
    static const long value = n * Multiply<Others...>::value;
};

template <>
class Multiply<> {
public:
    static const long value = 1;
};

//----------------------- variadic template function -----------------------
// 3. more powerful printf.
void Printf( const char * s ) {
    while ( *s ) {
        if ( *s == '%' && *++s != '%' ) {
            throw std::runtime_error( "missing arguments" );
        }
        std::cout << *s++;
    }
}

template <typename T, typename ... Args>
void Printf( const char * s, T val, Args...args ) {
    while ( *s ) {
        if (*s == '%' && *++s != '%')
        {
            // val's type is known. not like va_arg(args, type).
            std::cout << val;              
            return Printf( ++s, args... );
        }
        std::cout << *s++;
    }
    // here is unreachable, if args of printf is correct.
    throw std::runtime_error( "too much args variables." );
}

//---------------------- example of unpack  ----------------------
// 4. variadic print util
template <typename ... Args> void DummyWrapper(const Args&... args) {}
template <typename T> 
const T& print(const T& t) {
	std::cout << t;
	return t;
}

template <typename ... Args>
void vPrint(const Args&... args) {
	DummyWrapper(print(args)...);
	// DummyWrapper(args)...; // error.
}

//---------------------- example of sizeof... ----------------------
// 5. sizeof ..., return the number of the variadic in the template.
template <typename ... Args>
class VariadicCount {
public:
	static const size_t value = sizeof...(Args);
};

template <typename ... Args>
size_t numOfVariadic(Args...args) {
	return sizeof...(Args);
}

//---------------------- template variadic template ----------------------
// define a container, use type T as its inside class's template type.
template <typename T, template<typename> class ... Args> class Container;

template <typename T, template<typename> class Head, 
		  template<typename> class ... Others>
class Container<T, Head, Others...> {
public:
	Head<T> a;
	Container<T, Others...> b;
};

template <typename T> class Container<T> {};

// auxiliary class for testing template variadic template
template <typename T> class A {};
template <typename T> class B {};

//-------- perfect forward using template variadic template function ----------
// Fa, Fb is classes to be forwarded.
class Fa {
public:
	Fa() {}
	Fa(const Fa& fa) {
		pln("Fa copied");
	}
	Fa(Fa&& fa) {
		pln("Fa moved");
	}
};

class Fb {
public:
	Fb() {}
	Fb(const Fb& fb) {
		pln("Fb copied");
	}
	Fb(Fb&& fb) {
		pln("Fb moved");
	}
};

// wrapper.
template <typename ... Args> class MultiTypes;
template <typename T, typename ... Others>
class MultiTypes<T, Others...> : public MultiTypes<Others...>{
public:
	T t_;
	MultiTypes<T, Others...>(T t, Others... others) 
		: t_(t), MultiTypes<Others...>(others...) {
		pln("construct MutiTypes<T, Others...>");
	}
    /* error.  how to get base's t_ ?
    T& getBaseT() {
        if (sizeof...(Others) > 0)
        {
            return Multiply<Others...>::t_;
        }
        return t_;
    }
    */
};

template <> class MultiTypes<> {};

// use template function to forward.
template <template<typename...> class Multi, typename... Args>
Multi<Args...> build(Args&&... args) {
	return Multi<Args...>(std::forward<Args>(args)...);
}


NS_END( variadic_template )
NS_END( elloop )