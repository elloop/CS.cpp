#include "inc.h"
#include <vector>
#include <numeric>
#include <algorithm>

NS_BEGIN(elloop);

using namespace std;

vector<int> mthPerm(int n, int m) {
    assert(n > 0 && m > 0);
    vector<int> result;
    result.reserve(n);
    result.resize(n);
    iota(result.begin(), result.end(), 1);
    --m;
    while (m--) {
        next_permutation(result.begin(), result.end());
    }
    return result;
}

BEGIN_TEST(NextPerm, Basic, @@);

auto result = mthPerm(10, 3);
printContainer(result, "m-th permutation: ");

END_TEST;

NS_END(elloop);
