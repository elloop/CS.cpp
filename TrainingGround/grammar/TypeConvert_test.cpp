#include "TypeConvert_test.h"
#include "gtest/gtest.h"
#include "inc.h"

NS_BEGIN(elloop);

using namespace std;

TEST(TypeConvertTest, OperatorAndConvert) {
  pcln("TypeConvertTest --> OperatorAndConvert");
  Convertable ct(10);
  psln(ct());

  // using type convert operator.
  double d(ct); // ok!
  //double d = ct;  // no, operator double() is expicit.
  psln(d);

  //Convertable ct2 = d;  // explicit ctr().
}
NS_END(elloop);