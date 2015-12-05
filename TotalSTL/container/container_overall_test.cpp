#include "container/container_overall_test.h"
#include "stl_headers.h"

using std::vector;
using std::set;
using std::unordered_map;

NS_BEGIN(elloop);
NS_BEGIN(container_overall);

//----------------------------------- begin of new test-----------------------
BEGIN_TEST(Container, SetInMap, @@);
//put a set into map
// modify the set through iterator
set<int> si;
si.insert(10);
unordered_map<int, set<int>> setmap;
setmap.insert({1, si});

auto iter = setmap.find(1);
if (iter != setmap.end()) 
{
    //auto seti = iter->second; // won't change set in the map
    auto& seti = iter->second;  // would change set in the map.
    seti.insert(1000);
}

printContainer(si, "si: ");

for (auto seti : setmap) 
{
    printContainer(seti.second, "seti: ");
}

END_TEST;


//----------------------------------- begin of new test-----------------------
RUN_GTEST(Container, InvalidIterator, @@);

set<int> si;
si.insert(10);

// set's iterator won't be invalid during visiting even if i insert new things.
for (auto i : si) 
{
    psln(i);
    if (i < 100) 
    {
        si.insert(i+10);
    }
}

auto iter1 = si.begin();
while (iter1 != si.end())
{
    psln(*iter1);
    if (*iter1 < 100) 
    {
        si.insert(10 + *iter1);
    }
    ++iter1;
}

// vector's iterator would be invalid during visiting when i push new things.
vector<int> vi;
vi.push_back(10);

auto iter2 = vi.begin();
while (iter2 != vi.end())
{
    psln(*iter2);
    //vi.push_back(*iter2 + 1);      // cause assert failure.
    ++iter2;
}

for (auto i : vi)
{
    psln(i);
    //vi.push_back(i + 1);        // cause assert failure.
}

END_TEST;

NS_END(container_overall);
NS_END(elloop);

