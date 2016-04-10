#if defined(_MSC_VER)
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>

NS_BEGIN(elloop);

class Convertable {
public:
  explicit Convertable(int i=0) : i_(i) {}

  // 注意下面两个概念，

  // 1. 重载()操作符
  int operator() () { return i_; }

  // 2. 类型转换操作符
  explicit operator double() {
    return i_;
  }

  int i_;
};

NS_END(elloop);
