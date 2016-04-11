#ifdef _MSC_VER
#pragma once
#else
_Pragma( "once" )
#endif
#include "inc.h"

NS_BEGIN( elloop )
NS_BEGIN( alignof_alignas )



// ALIGNOF is like sizeof, it return a std::size_t type, indicate how many
// bytes the data is align. it's a platform related value.

// TODO: followings wait to be completed.
// ALIGNAS

// std::align
// std::align_storage
// std::align_union

NS_END(alignof_alignas )
NS_END(elloop )