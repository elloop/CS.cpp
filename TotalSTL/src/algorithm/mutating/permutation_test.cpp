#include "inc.h"
#include <vector>
#include <algorithm>
#include <numeric>

NS_BEGIN(elloop);

using namespace std;

static std::string format(const char *fmt, ...) {
    va_list args, args1;
    va_start(args, fmt);
    va_copy(args1, args);

    string res(1 + vsnprintf(nullptr, 0, fmt, args1), 0);
    va_end(args1);

    vsnprintf(&res[0], res.size(), fmt, args);
    va_end(args);

    return res;
}

// ****************************************************************************
BEGIN_TEST(PermutationTest, Basic, @);

vector<int> v;
v.resize(3);
iota(v.begin(), v.end(), 1);

int count(0);
do {
    printContainer(v, format("the %d-th perm: ", ++count));
} while (next_permutation(v.begin(), v.end()));

pln(format("total perm: %d", count));

END_TEST;


NS_END(elloop);
