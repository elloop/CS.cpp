#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include <type_traits>
#include "messi.h"
#include "inc.h"

NS_ELLOOP_BEGIN

class PodTest : Messi {
  public:
    PodTest* run() override;
};

class t1 {
};

class t2 : public t1 {
};

class nt1 {
public:
  nt1() {
    pln("this is non-trivial");
  }
};

class nt2 {
public:
  virtual void f() {}
};

NS_ELLOOP_END
