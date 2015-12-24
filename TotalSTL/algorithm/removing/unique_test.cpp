#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;



//----------------------- ShuffleWithGenerator  ----------------------
BEGIN_TEST(UniqueTest, Basic, @);

vector<int> v{1, 2, 3, 4, 5, 6, 7 , 8, 10, 2, 3, 5, 9, 10, 1, 4, 4, 3, 3};
printContainer(v, "v: ");

sort(v.begin(), v.end());
auto iter = unique(v.begin(), v.end());
if ( iter != v.end() )
{
    v.resize(distance(v.begin(), iter));
}
printContainer(v, "v: ");

END_TEST;




NS_END(elloop);