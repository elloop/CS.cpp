#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"

NS_BEGIN(elloop)
NS_BEGIN(strongly_typed_enum)

//drawback of old enum: (非强作用域类型)
// 1. namespace pollution, enum's value auto inject into global namespace.
// 2. convert to int implicitly.
// 3. 占用空间不确定

// new enum in cpp11.
// 1. use class keyword
// 2. a base_type is optional, which specifies the type used in enum.

using base_type = int;
//using base_type = unsigned int;
//using base_type = wchar_t; //should cause a error, but passes in vs2013.
enum class Animal : base_type { kDog=-111, kCat };

// without base_type, default is int.
enum class Car { kJeep, kTank};


NS_END(strongly_typed_enum)
NS_END(elloop)