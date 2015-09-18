#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif
#include "inc.h"
#include <map>
NS_ELLOOP_BEGIN

// using 定义数据类型，功能比typedef更加强大，除了typedef能做到的一般功能以外
//，using在模板编程中更加灵活。


template<typename T>
using IntMap = std::map<T, int>;

NS_ELLOOP_END