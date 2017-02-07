#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <vector>

NS_BEGIN(elloop);
using namespace std;

//********************************** new case **********************************
BEGIN_TEST(VectorTest, BasicUse, @);

vector<int> vi {1, 2, 3};

// add elems
for (int i=4; i<10; ++i) 
{
    vi.push_back(i);
}

// random access and modify
vi[0] = 10;

// print elems
printContainer(vi, "init vi: ");

// delete
auto iter = vi.begin();
vi.erase(iter);
printContainer(vi, "erase begin, vi: ");

iter = find(vi.begin(), vi.end(), 5);
if (iter != vi.end()) {
    pln("erase 5");
    vi.erase(iter);
}
printContainer(vi, "erase 5, vi: ");

END_TEST;

//********************************** new case **********************************
BEGIN_TEST(VectorTest, Capacity, @);

vector<int> v1;
psln(v1.capacity());

vector<int> v2(10);
psln(v2.capacity());

vector<int> v3 = {1};
psln(v3.capacity());

v3.reserve(10);
psln(v3.capacity());

END_TEST;

//********************************** new case **********************************

template <typename T>
void shrinkCapacity(vector<T> &v) {
    vector<T> temp(v);
    temp.swap(v);
}

BEGIN_TEST(VectorTest, Shrink, @@);

vector<int> vi;

vi.reserve(30);
vi.push_back(1);

psln(vi.capacity());        // 30

shrinkCapacity(vi);

vi.shrink_to_fit();         // since c++ 11

psln(vi.capacity());        // 1



END_TEST;

NS_END(elloop);
