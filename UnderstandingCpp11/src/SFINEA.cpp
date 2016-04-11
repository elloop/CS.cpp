#include "SFINEA.h"
#include "gtest/gtest.h"

NS_ELLOOP_BEGIN
namespace sfinea {

    BEGIN_TEST( SFINEA, Basic, @);
        // Foo has Foo::inside_type, so called f(T::inside_type).
        f<Foo>( 1 );

        // althoug int has no int::inside_type, compiler doesn't 
        // complain, instead it check and call f(T).
        f<int>( 1 ); 
    END_TEST;

}

NS_ELLOOP_END