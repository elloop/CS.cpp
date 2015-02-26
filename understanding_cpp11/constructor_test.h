_Pragma("once")

#include "base_test.h"
NS_ELLOOP_BEGIN

class ConstructorTest : public BaseTest {
  public:
    // target constructor.
    ConstructorTest() {
      init();
      if (distance_ < 5) {
        throw 1;
      }
    }

    // deleagte constructor 1.
    ConstructorTest(int i) : try {
      ConstructorTest()
    }
    catch(...) {
      pln("catch exception in ConstructorTest().");
    }
    {
      i_ = i;
    }

    // deleagte constructor 2.
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
    float f_ {1.111};
    float distance_ = 0;
};

NS_ELLOOP_END

