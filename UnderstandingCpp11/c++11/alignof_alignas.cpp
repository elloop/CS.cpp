#include "alignof_alignas.h"

NS_BEGIN( elloop )
NS_BEGIN( alignof_alignas )

TEST( Align, Alignof ) {
#ifdef _MSC_VER
#else
    int a;
    long long ll;
    auto & c = ll;
    char carry[1024];
    //psln( alignof( int ) );
#endif
    
}

TEST( Align, Alignas ) {
#ifdef _MSC_VER
#else
    alignas(10) char c;
    alignas( double ) char c1;
    alignas(alignof(double)) c2;
#endif

}

NS_END( alignof_alignas )
NS_END( elloop )