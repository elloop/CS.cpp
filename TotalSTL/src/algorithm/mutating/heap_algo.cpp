#include "inc.h"
#include "stl_headers.h"
#include <vector>
#include <functional>
#include <algorithm>

NS_BEGIN(elloop);

using namespace std;

// ****************************************************************************
BEGIN_TEST(HeapAlgo, MakeHeap, @@);

vector<int> v1{6, 1, 2, 5, 3, 4};
printContainer(v1, "v1 before make_heap: ");
make_heap(v1.begin(), v1.end());
printContainer(v1, "v1 after make_heap: ");
sort_heap(v1.begin(), v1.end());
printContainer(v1, "v1 after sort_heap: ");
cr;

vector<int> v2{6, 1, 2, 5, 3, 4};
printContainer(v2, "v2 before make_heap: ");
make_heap(v2.begin(), v2.end(), greater<int>());
printContainer(v2, "v2 after make_heap: ");
sort_heap(v2.begin(), v2.end(), greater<int>());
printContainer(v2, "v2 after sort_heap: ");

END_TEST;

// ****************************************************************************
// push_heap(beg, end):
// the caller has to ensure that elements in the range [beg, end) are a heap.(according to the same sorting criterion)
BEGIN_TEST(HeapAlgo, PushHeap, @@);

vector<int> v1{6, 1, 2, 5, 3, 4};
make_heap(v1.begin(), v1.end());

v1.push_back(200);
printContainer(v1, "v1 before push_heap: ");
push_heap(v1.begin(), v1.end());
printContainer(v1, "v1 after push_heap: ");

// wrong!
vector<int> v2{6, 1, 2, 5, 3, 4};
v2.push_back(200);
printContainer(v2, "v2 before push_heap: ");
push_heap(v2.begin(), v2.end());
printContainer(v2, "v2 after push_heap: ");

END_TEST;

// ****************************************************************************
// pop_heap: the caller also has to ensure the elements in the range [beg, end) are a heap (according the same sorting criterion).
BEGIN_TEST(HeapAlgo, PopHeap, @@);

vector<int> v1{6, 1, 2, 5, 3, 4};
make_heap(v1.begin(), v1.end());
printContainer(v1, "after make_heap: ");

pop_heap(v1.begin(), v1.end());
printContainer(v1, "after pop_heap: ");
auto largest = v1.back();
psln(largest);
v1.pop_back();
printContainer(v1, "delete largest: ");

END_TEST;

// ****************************************************************************
BEGIN_TEST(HeapAlgo, SortHeap, @@);

vector<int> v1{6, 1, 2, 5, 3, 4};
printContainer(v1, "before sort_heap: ");

make_heap(v1.begin(), v1.end());

sort_heap(v1.begin(), v1.end());
printContainer(v1, "after sort_heap: ");

END_TEST;

// ****************************************************************************
BEGIN_TEST(HeapAlgo, IsHeap, @@);

vector<int> v1{6, 1, 2, 5, 3, 4};
psln(is_heap(v1.begin(), v1.end()));

pln("after make_heap");

make_heap(v1.begin(), v1.end());
psln(is_heap(v1.begin(), v1.end()));

END_TEST;

// ****************************************************************************
BEGIN_TEST(HeapAlgo, IsHeapUntil, @@);

vector<int> v1{6, 1, 2, 5, 3, 4};
auto iter = is_heap_until(v1.begin(), v1.end());
psln(*iter);        // *iter = 5

make_heap(v1.begin(), v1.end());
iter = is_heap_until(v1.begin(), v1.end());
ASSERT_TRUE(iter == v1.end());

END_TEST;


// ****************************************************************************
BEGIN_TEST(HeapAlgo, BasicUse, @@);

vector<int> vi{6, 1, 2, 5, 3, 4};
printContainer(vi, "vi: ");

make_heap(vi.begin(), vi.end());
printContainer(vi, "vi: ");

vi.push_back(200);
push_heap(vi.begin(), vi.end());
printContainer(vi, "vi: ");

pop_heap(vi.begin(), vi.end());
auto largest = vi.back();
psln(largest);                      // 200
vi.pop_back();

END_TEST;


NS_END(elloop);
