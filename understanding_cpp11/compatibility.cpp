#include "compatibility.h"
#include "inc.h"

#include <climits>
#include <iostream>

USING_NS_STD;
USING_NS_ELLOOP;

//---------------------------------- test in this cpp ------------------------------------
void testC99Macro(); 
void testLongLong();
void testNoexcept() { }

Compatibility * Compatibility::run() {
    LOGD("in function : %s\n", __func__);
    LOGD("__cplusplus : %ld\n", __cplusplus);

    testC99Macro();

    // testLongLong();
    return this;
}

//----------------------------------------------------------------------
// test C99 macro
//----------------------------------------------------------------------
void testC99Macro() {

  LOGD("Standard Clib: %d\n", __STDC_HOSTED__);
  // psln(__STDC_HOSTED__);
  
  LOGD("Standard C: %d\n", __STDC__);
  // psln(__STDC__);
  
  // psln(__STDC_VERSION__);
  // LOGD("C Standard Version: %d\n", __STDC_VERSION__);
  
  LOGD("ISO/IEC: %ld\n", __STDC_ISO_10646__);
  // psln(__STDC_ISO_10646__);
}


//----------------------------------------------------------------------
// long long keyword.
//----------------------------------------------------------------------
void testLongLong() {
  long long ll_min = LLONG_MIN;
  LOGD("long long min: %lld\n", ll_min);

  long long ll_max = LLONG_MAX;
  LOGD("long long max: %lld\n", ll_max);

  unsigned long long ull_max = ULLONG_MAX;
  LOGD("unsigned long long max: %llu\n", ull_max);
}

//----------------------------------------------------------------------
// noexcept used as:
// 1. specifier. used in plain function definittion. 
//    void f() noexcept { }
//    void g() noexcept(false) { }
//
// 2. operator. used in template function :
//    template <typename T>
//    void func() noexcept(noexcept(T())) { }
//
// In default, destructor is noexcept(true).
//
// if a noexcept(true) function throws a exception(s), std::terminate() will be called.
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// friend extend.
// 1. friend class A --> friend A;
// 2. typedef A AA; 
//    friend AA;  // ok.
// 3. friend of template class is ok.
//    template <typename T>
//    class B {
//      friend T;
//    };
//    // T is friend class of B<T>.
//    // if T is not user type, such as int, float ..., friend is ignore.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// quick init member variables.
// class A {
// public:
//
//   A(int i) : i_(1000), f_(100) // init list come second.
//   { 
//     i_ = i;    // come last.
//   }
//
//   int i_ = 0;  // come first.
//
//   float f_ {1.11};
//
// };
// A a(-1);
//
// finally, a.i_ will be -1; a.f_ will be 100.
//
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// extern template declaration.
//
// avoid compiler generate duplicate copies of the same function of a template.
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// template actual parameters extend.
// template <typename T> class X {};
// template <typename T> f(T t) {};
//
// use:
// 1. local struct. { struct A {} a; X<A>; f(a); }
// 2. anonymous struct. typedef struct { int i;} B; X<B>;
// 3. struct { int i;} b; f(b);
//----------------------------------------------------------------------

