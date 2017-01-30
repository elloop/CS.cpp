#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <vector>

NS_BEGIN(elloop);
using namespace std;

//********************************** new case **********************************
RUN_GTEST(VectorTest, BasicUse, @);

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

END_TEST;

//********************************** new case **********************************

NS_END(elloop);
