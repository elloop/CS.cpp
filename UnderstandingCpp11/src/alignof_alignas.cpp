#include "alignof_alignas.h"

NS_BEGIN( elloop )
NS_BEGIN( alignof_alignas )

BEGIN_TEST( Align, Alignof , @);
#ifdef _MSC_VER
#else
    int a;
    long long ll;
    auto & c = ll;
    char carry[1024];
    //psln( alignof( int ) );
#endif
    
END_TEST;

BEGIN_TEST( Align, Alignas, @);
#ifdef _MSC_VER
#else
    //alignas(10) char c; // error: requested alignment is not a power of 2
    alignas(8) char c;
    alignas( double ) char c1;
    alignas(alignof(double)) char c2;
#endif

END_TEST;

NS_END( alignof_alignas )
NS_END( elloop )
