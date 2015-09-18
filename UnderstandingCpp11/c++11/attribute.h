#ifdef _MSC_VER
#pragma once
#else
_Pragma( "once" )
#endif
#include "inc.h"

NS_BEGIN( elloop )
NS_BEGIN( attribute )

// there are only two attributes in cpp11:
// 1. [[noreturn]]
// 2. [[carries_dependency]]

#ifdef _MSC_VER
#else
[[noreturn]]void throwAway();
#endif

NS_END(attribute )
NS_END(elloop )