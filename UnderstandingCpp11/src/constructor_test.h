#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif // _MSC_VER

#include "messi.h"
NS_ELLOOP_BEGIN

class ConstructorTest : public Messi {
  public:
    // target constructor.
    ConstructorTest() {
      init();
      if (distance_ < 5) {
        throw 1;
      }
    }

    // delegate constructor 1.
    ConstructorTest(int i) try : ConstructorTest() {
      i_ = i;
    }
    catch(...) {
      pln("catch exception in ConstructorTest().");
    }

    // delegate constructor 2.
    ConstructorTest(int i, float f) : ConstructorTest(i) {
      f_ = f;
    }

    ConstructorTest(int i, float f, float distance) : ConstructorTest(i, f) {
      distance_ = distance;
    }

    void p() {
      psln(i_);
      psln(f_);
      psln(distance_);
    }

    ConstructorTest * run() final override;
  private:
    void init() {
      i_ *= 2;
      f_ *= 2;
      distance_ = i_ + f_;
    }

    void initMayThrow() {
      throw 2;
    }

    int i_ = 1;
    float f_ {1.111f};
    float distance_ = 0;
};

NS_ELLOOP_END

