#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(range_based_for_loop)

// Usage:
// 1. for (T t: vec)
// 2. for (T &t:vec)
// 3. for (T e:stl_container), e is not iterator, it's result of dereference.


// many stl containers like vector, list, map, set, dequeue ... 
// and
// array type are surpported.

// used with user-defined data structure
// you should implement begin(), end() and implement ++ and == operator for the
// iter.


NS_END(range_based_for_loop)
NS_END(elloop)