#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;



//----------------------- RandomShuffle  ----------------------
BEGIN_TEST(ShuffleTest, RandomShuffle, @);

array<int, 10> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
printContainer(a, "a: ");
cr;
cr;

for (int i=0; i<10; ++i) 
{
    random_shuffle(a.begin(), a.end());
    printContainer(a, "a: ");
}

END_TEST;


//----------------------- ShuffleWithGenerator  ----------------------
BEGIN_TEST(ShuffleTest, ShuffleWithGenerator, @);

array<int, 10> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
printContainer(a, "a: ");
cr;
cr;
int b(5);
vector<int> bb;
bb.assign(a.begin(), a.begin() + b);
printContainer(bb, "bb: ");

for (int i = 0; i < 10; ++i)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(a.begin(), a.end(), default_random_engine(seed));
    printContainer(a, "a: ");
    bb.assign(a.begin(), a.begin() + b);
    printContainer(bb, "bb: ");
    
}

END_TEST;



NS_END(elloop);