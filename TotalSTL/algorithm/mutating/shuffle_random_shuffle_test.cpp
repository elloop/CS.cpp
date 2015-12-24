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




RUN_GTEST(ShuffleTest, Default, @);

array<int, 10> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
printContainer(a, "a: ");

random_shuffle(a.begin(), a.end());     // use default rand().
printContainer(a, "a: ");

sort(a.begin(), a.end());
printContainer(a, "a: ");

default_random_engine defaultEngine;    // default engine.
shuffle(a.begin(), a.end(), defaultEngine);
printContainer(a, "a: ");

sort(a.begin(), a.end());
printContainer(a, "a: ");

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine withSeed(seed);
shuffle(a.begin(), a.end(), withSeed);
printContainer(a, "a: ");

END_TEST;



class SelfGenerator
{
public:
    ptrdiff_t operator() (ptrdiff_t max)
    {
        double temp;
        temp = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        return static_cast<ptrdiff_t>(temp * max);
    }
};


//----------------------- self-written generator  ----------------------
RUN_GTEST(ShuffleTest, ShuffleWithGenerator, @);

array<int, 10> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
printContainer(a, "a: ");

SelfGenerator sg;
random_shuffle(a.begin(), a.end(), sg);

printContainer(a, "a: ");

END_TEST;



NS_END(elloop);