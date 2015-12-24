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


void uniqueUrls(std::vector<int> &v)
{
    sort(v.begin(), v.end());
    auto iter = unique(v.begin(), v.end());
    if (iter != v.end())
    {
        v.resize(distance(v.begin(), iter));
    }
}

//----------------------- ShuffleWithGenerator  ----------------------
RUN_GTEST(UniqueTest, Basic, @);

vector<int> v{1, 2, 3, 4, 5, 6, 7 , 8, 10, 2, 3, 5, 9, 10, 1, 4, 4, 3, 3};
printContainer(v, "v: ");
uniqueUrls(v);
printContainer(v, "v: ");

//time_t ti;
//time(&ti);
//psln(ctime(&ti));

time_t rawtime;
struct tm * timeinfo;
char buffer[80];

time(&rawtime);
timeinfo = localtime(&rawtime);

strftime(buffer, 80, "[%H:%M:%S]", timeinfo);
puts(buffer);

END_TEST;



NS_END(elloop);