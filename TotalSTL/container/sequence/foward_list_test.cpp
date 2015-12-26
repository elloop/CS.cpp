#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>
#include <forward_list>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;




//----------------------- forward_list basic  ----------------------
RUN_GTEST(ForwardListTest, Basic, @);

forward_list<int> fl = { 1, 2, 3, 4, 5 };
for (const auto &elem : fl)
{
    psln(elem);
}

psln(fl.front());

END_TEST;




//----------------------- Modifying  ----------------------
RUN_GTEST(ForwardListTest, Modifying, @);

forward_list<int> fl = { 1, 2, 3 };
printContainer(fl, "fl: ");                 // fl: 1 2 3

fl.insert_after(fl.before_begin(), 10);
printContainer(fl, "fl: ");                 // fl: 10 1 2 3

fl.erase_after(fl.before_begin());
printContainer(fl, "fl: ");                  // fl: 1 2 3

END_TEST;





//----------------------- find and modify  ----------------------
RUN_GTEST(ForwardListTest, FindAndModify, @);

forward_list<int> fl = { 1, 2, 3 };
printContainer(fl, "fl: ");                 // fl: 1 2 3

// find first even number.
auto isEven = [](int i) -> bool
{
    return (i % 2 == 0);
};

auto deletePos = find_if(fl.begin(), fl.end(), isEven);

// deletePos is walk too far, i need a position before this.


forward_list<int>::iterator beforePos, pos;

beforePos = fl.before_begin();

for (pos = fl.begin(); pos != fl.end(); beforePos = pos, ++pos)
{
    if (*pos % 2 == 0)
    {
        break;
    }
}

if (pos != fl.end())
{
    // now beforePos can be passed to erase_after()
    fl.erase_after(beforePos);
    printContainer(fl, "fl: ");                 // fl: 1 3
}

// recover fl to 1 2 3.
fl.insert_after(beforePos, 2);
printContainer(fl, "fl: ");                     // fl: 1 2 3

// use next(pos, n=1).
beforePos = fl.before_begin();
for (; next(beforePos) != fl.end(); ++beforePos)
{
    int i = *next(beforePos);
    if (isEven(i))
    {
        break;
    }
}


if (next(beforePos) != fl.end()) 
{
    // find the pos.
    fl.erase_after(beforePos);
    printContainer(fl, "fl: ");              // fl: 1 3
}


END_TEST;




//----------------------- test find_before  ----------------------
RUN_GTEST(ForwardListTest, FindBefore, @);

forward_list<int> fl = { 1, 2, 3 };
printContainer(fl, "original fl: ");                 // 1 2 3

//------------------ find_before -----------------------
auto posBefore2 = find_before(fl.begin(), fl.end(), 2);
if (posBefore2 != fl.end()) 
{
    fl.erase_after(posBefore2);
    printContainer(fl, "delete 2: ");                 // 1 3
}


//------------------ find_before_if -----------------------
auto isEven = [](int i) -> bool
{
    return (i % 2 == 0);
};

// recover fl contents to 1 2 3.
fl.clear();
fl.insert_after(fl.before_begin(), {1, 2, 3});
printContainer(fl, "original fl: ");                 // 1 2 3


posBefore2 = find_before_if(fl.begin(), fl.end(), isEven);
if (posBefore2 != fl.end()) 
{
    fl.erase_after(posBefore2);
    printContainer(fl, "delete first even: ");      // 1 3
}


END_TEST;

NS_END(elloop);