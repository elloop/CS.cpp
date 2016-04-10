#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>
#include <forward_list>
#include <tuple>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;




BEGIN_TEST(TupleTest, MemberFunction, @);

tuple<int, char, bool> tu1(1, 'a', true);

// get<i>
int     i = get<0>(tu1);
char    c = get<1>(tu1);
bool    b = get<2>(tu1);

EXPECT_EQ(1, i);
EXPECT_EQ('a', c);
EXPECT_EQ(true, b);

tie(i, c, b) = tu1;
EXPECT_EQ(1, i);
EXPECT_EQ('a', c);
EXPECT_EQ(true, b);

tuple<int, char, bool> tu2 = make_tuple(i, c, b);
EXPECT_EQ(tu2, tu1);
END_TEST;



NS_END(elloop);