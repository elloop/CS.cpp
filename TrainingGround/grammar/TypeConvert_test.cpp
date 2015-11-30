#include "TypeConvert_test.h"
#include "gtest/gtest.h"
#include "inc.h"

NS_BEGIN(elloop);

using namespace std;

<<<<<<< HEAD
BEGIN_TEST(TypeConvertTest, OperatorAndConvert, @)
  pcln("TypeConvertTest --> OperatorAndConvert");
  Convertable ct(10);
  psln(ct());
=======
BEGIN_TEST(TypeConvertTest, OperatorAndConvert, @);
pcln("TypeConvertTest --> OperatorAndConvert");
Convertable ct(10);
psln(ct());
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

// using type convert operator.
double d(ct); // ok!
//double d = ct;  // no, operator double() is expicit.
psln(d);

//Convertable ct2 = d;  // explicit ctr().
END_TEST;

<<<<<<< HEAD
  //Convertable ct2 = d;  // explicit ctr().
END_TEST

=======
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340
NS_END(elloop);