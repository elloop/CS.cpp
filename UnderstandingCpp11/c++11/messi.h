#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include "inc.h"

NS_ELLOOP_BEGIN

class Messi {
  public:
    virtual ~Messi() {
      pcln("deleting a test.");
    }

    Messi() {
      pcln("creating a test.");
    }

    // BaseTest(int id) : id_(id) {
    //   pcln("creating a test.");
    // }

    virtual Messi * run() = 0;
  private:
    int id_;
};

NS_ELLOOP_END
