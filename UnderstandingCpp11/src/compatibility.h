#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include "inc.h"
#include "messi.h"

NS_ELLOOP_BEGIN

#ifdef _MSC_VER

#if __cplusplus < 201103L
#endif

#else
#if __cplusplus < 201103L
#error "should use c++11 complier."
#endif 

#endif// _MSC_VER

static_assert(sizeof(int) == 4, "sizeof int should be 4 bytes.");

template <typename T> class Printer;

class Compatibility : public Messi {
public:
	// using BaseTest::BaseTest(10);
	Compatibility * run() final override;
private:
	// local init.
	int i_ = 0;
	float f_{ 1.1f };

	// new friend grammar.
	friend Printer<Compatibility>;
};

// test final keyword.
class Dc : public Compatibility {
public:
	// Dc * run()  {return this;} // error: run() is final in base-class Compatibility.
};

// total template definition.
template <typename T>
class Printer {
public:
	void p(const T & t) {
		pcln("in Printer<T>");
	}
};

// partial specialization.
template <>
class Printer<Compatibility> {
public:
	void p(const Compatibility & t) {
		psln(t.i_);
		psln(t.f_);
	}
};


NS_ELLOOP_END
