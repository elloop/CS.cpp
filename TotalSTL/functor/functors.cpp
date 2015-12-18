#include "functors.h"

NS_BEGIN(elloop);

using std::modulus;
using std::bind1st;
using std::bind2nd;
using std::greater;
using std::less;
using std::equal;




BEGIN_TEST(FunctorTest, Useful, @);
  // modulus
  modulus<int> mIntFunc;
  EXPECT_EQ(1, mIntFunc(7, 6));

END_TEST;




NS_END(elloop);