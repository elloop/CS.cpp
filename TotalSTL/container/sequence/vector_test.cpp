#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <vector>

NS_BEGIN(elloop);
using namespace std;



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
for (int elem : vi)
{
    pln(elem);
}

END_TEST;




RUN_GTEST(VectorTest, Capacity, @);

vector<int> v1;
psln(v1.capacity());

vector<int> v2(10);
psln(v2.capacity());

vector<int> v3 = {1};
psln(v3.capacity());


END_TEST;


NS_END(elloop);