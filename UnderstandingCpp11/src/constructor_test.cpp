#include "constructor_test.h"

NS_ELLOOP_BEGIN

ConstructorTest* ConstructorTest::run() {
  ConstructorTest t;
  t.p();

  ConstructorTest t1(1);
  t1.p();

  ConstructorTest t2(1, 1);
  t2.p();

  ConstructorTest t3(0, 111, true);
  t3.p();

  return this;
}
NS_ELLOOP_END
