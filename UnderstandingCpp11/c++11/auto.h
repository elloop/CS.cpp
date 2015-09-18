#ifdef _MSC_VER
#pragma once
#else
_Pragma( "once" )
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(auto_test)

// TODO: error: ??
//#define Max(a, b) { \
//	(auto aa = (a); \
//	auto bb = (b); \
//	(aa > bb) ? aa : bb;) \
//}

// notice:
// 1. auto & a = b; defining a reference use auto, must with '&'.
// 2. auto doesn't take away c-v qualifier. 
//		const auto a = b;
//		auto c = a; // c is not const.
// 3. when defining several vairables using auto, only the first variable's type
//    is deduced, and the left variables are define use the result of  first 
//    type. like type substitution.

NS_END(auto_test)
NS_END(elloop)