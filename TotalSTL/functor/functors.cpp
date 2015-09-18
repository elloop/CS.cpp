#include "functors.h"

NS_BEGIN(elloop);

using std::modulus;
using std::bind1st;
using std::bind2nd;
using std::greater;
using std::less;
using std::equal;


TEST(FunctorTest, Useful) {
  // modulus
  modulus<int> mIntFunc;
  EXPECT_EQ(1, mIntFunc(7, 6));

}

NS_END(elloop);