#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;






void printFun(int i)
{
    cout << i << " ";
}
//----------------------- for_each non-modify----------------------
RUN_GTEST(ForEachTest, NonModify, @);

auto print = [](int i){ cout << i << " "; };

vector<int> v{1,2,3,4,5};
for_each(v.begin(), v.end(), print);
cr;

for_each(v.begin(), v.end(), printFun);
cr;

END_TEST;




template <typename T>
class AddVal
{
public:
    AddVal(const T& val) : val_(val)
    {}

    void operator() (T & val)
    {
        val += val_;
    }

private:
    T val_;
};

void add50(int &val)
{
    val += 50;
}
//----------------------- for_each modify----------------------
RUN_GTEST(ForEachTest, Modify, @);

vector<int> coll;
insertElements(coll, 1, 5);
printContainer(coll, "coll: ");  // coll: 1 2 3 4 5 

// change use lambda.
for_each(coll.begin(), coll.end(),
         [](int& elem){ elem += 50; });

printContainer(coll, "coll: ");  //coll: 51 52 53 54 55 


// change use functor
for_each(coll.begin(), coll.end(),
         AddVal<int>(50));

printContainer(coll, "coll: ");//coll: 101 102 103 104 105 

// change use function.
for_each(coll.begin(), coll.end(), add50);
printContainer(coll, "coll: ");//coll: 151 152 153 154 155 

END_TEST;




class MeanValue
{
public:
    MeanValue() : count_(0), sum_(0) {}
    void operator() (int val)
    {
        sum_ += val;
        ++count_;
    }
    operator double()
    {
        if ( count_ <= 0 )
        {
            return 0;
        }
        return sum_ / count_;
    }
private:
    double      sum_;
    int         count_;
};
//----------------------- for_each return value----------------------
RUN_GTEST(ForEachTest, UseReturnValue, @);

vector<int> coll2{ 1, 2, 3, 4, 5 };
printContainer(coll2, "coll2:");   // coll2: 1 2 3 4 5

//for_each returns a copy of MeanValue(), then use operator double().
// same with:
// MeanValue mv = for_each(coll2.begin(), coll2.end(), MeanValue());
// double meanValue = mv;
double meanValue = for_each(coll2.begin(), coll2.end(),
                            MeanValue());
psln(meanValue);

// validate result using numeric.
using std::accumulate;
double sum(0);
sum = accumulate(coll2.begin(), coll2.end(), 0);
EXPECT_EQ(sum / coll2.size(), meanValue);

END_TEST;




//----------------------- range based for loop ----------------------
RUN_GTEST(ForEachTest, RangeForLoop, @);

//-----------non-modifying --------------
auto print = [](int i)
{
    cout << i << " ";
};

vector<int> v{ 1, 2, 3, 4, 5 };
//for_each(v.begin(), v.end(), print);
for (auto item : v)
{
    print(item);
}
cr;

//for_each(v.begin(), v.end(), printFun);
for (auto item : v)
{
    printFun(item);
}
cr;

//----------- modifying --------------
vector<int> coll;
insertElements(coll, 1, 5);
printContainer(coll, "coll: ");  // coll: 1 2 3 4 5 

for (auto & item : coll) {
    item += 50;
}
printContainer(coll, "coll: ");  //coll: 51 52 53 54 55 

END_TEST;


NS_END(elloop);