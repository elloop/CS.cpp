#ifdef _MSC_VER
#pragma once
#else
_Pragma( "once" )
#endif
#include "inc.h"

NS_ELLOOP_BEGIN

namespace sfinea {

// SFINEA : substitution failure is not an error.
// 这个机制被广泛用在STL中。
// 表现出来的效果是很符合程序员的预想的。

class Foo {
public:
    typedef int inside_type;
};

template<typename T>
void f( typename T::inside_type) {
    psln( "f(T::inside_type)" );
}

template<typename T>
void f( T ) {
    pln( "f(T)" );
}

}

NS_ELLOOP_END