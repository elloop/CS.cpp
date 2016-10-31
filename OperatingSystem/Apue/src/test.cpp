#include "include/inc.h"
#include <set>
#include <iterator>
#include <functional>
// #include <algorithm>
#include <numeric>

NS_BEGIN(elloop);

using namespace std;

// ****************************************************************************
BEGIN_TEST(CPPTest, Set, @@);

// approach 1:
set<int, greater<int>> s;
copy(istream_iterator<int>(cin), istream_iterator<int>(), inserter(s, s.begin()));
// cr;
copy(s.begin(), next(s.begin(), 2), ostream_iterator<int>(cout, " "));

// approach 2:
// set<int> s;
// copy(istream_iterator<int>(cin), istream_iterator<int>(), inserter(s, s.begin()));
//// copy_backward(prev(s.end(), 3), s.end(), ostream_iterator<int>(cout, " "));    // ostream_iterator is ForwardIterator can't go backward.
// reverse_copy(prev(s.end(), 2), s.end(), ostream_iterator<int>(cout, " "));
// cr;

// approach 3:
// set<int> s;
// reverse_copy(prev(copy(istream_iterator<int>(cin), istream_iterator<int>(), inserter(s, s.begin())), 3), s.end(), ostream_iterator<int>(cout, " "));

// approach 4:
// int a[10] = {0};
// copy(istream_iterator<int>(cin), istream_iterator<int>(), a);
// nth_element(a, a + 1, a+10, greater<int>());
// copy(a, a + 2, ostream_iterator<int>(cout, " "));


END_TEST;

// ****************************************************************************
// nth only assure comp(*j , *i) is false, not ensure left or right is sorted.
BEGIN_TEST(CPPTest, nth, @@);

vector<int> v{1, 2, 4, 5, 9, 0, 12, 8, 10};
nth_element(v.begin(), v.begin() + 2, v.end(), greater<int>());
copy(v.begin(), v.begin() + 3, ostream_iterator<int>(cout, " "));       // 10 12 9, not 12 10 9

END_TEST;

// ****************************************************************************
// version 1 CountPrimer
BEGIN_TEST(CPPTest, CountPrimer, @@);

int sum(0);
auto isPrime = [&sum](int n) -> bool {
    for (int i=2; i*i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    sum += n;
    return true;
};
int m(3), n(100);
vector<int> v(n - m + 1);
iota(v.begin(), v.end(), m);
psln(count_if(v.begin(), v.end(), isPrime));
psln(sum);

END_TEST;

// ****************************************************************************
// version 2 CountPrimer
RUN_GTEST(CPPTest, CountPrimer2, @@);


int m(3), n(100);
vector<int> v(n - m + 1);
iota(v.begin(), v.end(), m);

int sum(0), count(0);
for_each(v.begin(), v.end(), [&sum, &count](int i) {
        for (int j=2; j*j <= i; ++j) {
            if (i % j == 0) {
                return;
            }
        }
        sum += i;
        ++count;
}); 

pv("count: %d, sum: %d\n", count, sum);

END_TEST;


NS_END(elloop);

