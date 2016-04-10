#if defined(_MSC_VER)
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>
NS_BEGIN(elloop);

NS_BEGIN(smart_ptr);


class Dog {
public:
  int age_;
};
NS_END(smart_ptr);

NS_END(elloop);
