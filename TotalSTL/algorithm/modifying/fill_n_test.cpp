

#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <algorithm>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;




BEGIN_TEST(ModifyingAloritm, FillN, ++)
using std::string;

std::vector<string> vs;
std::fill_n(std::back_inserter(vs), 10, "ok");
printContainer(vs, "vs: ");

string s1;
std::fill_n(std::back_inserter(s1), 5, 'h');
psln(s1);

// output to stdout.
std::fill_n(std::ostream_iterator<string>(std::cout, " "), 5, "hello");

END_TEST;




NS_END(elloop);
