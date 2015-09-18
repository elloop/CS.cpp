#if defined(_MSC_VER)
#pragma once
#else
_Pragma("once")
#endif

#include "inc.h"
#include <string>

NS_BEGIN(elloop);

class HasRefAndConst {
public:
  HasRefAndConst(std::string&  str) : str_(str), i_(0) {
    LOGD("in constructor %s\n", __func__);
  }
  HasRefAndConst(const HasRefAndConst & other) : str_(other.str_), i_(other.i_) {
    LOGD("in copy constructor %s\n", __func__);
  }
  std::string& str_;
  const int i_;
};


NS_END(elloop);
