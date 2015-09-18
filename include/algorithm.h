#ifdef _MSC_VER
__pragma( "once" )
#else
_Pragma("once")
#endif

#include "inc.h"

NS_BEGIN(elloop);

template <typename T>
T max(T t1, T t2) {
  return ( t1 < t2 ) ? t2 : t1;
}

NS_END(elloop);
