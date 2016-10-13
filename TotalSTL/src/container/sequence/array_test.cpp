#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;



//----------------------- basic use ----------------------
BEGIN_TEST(ArrayTest, BasicUse, @);

array<int, 3> a;
for_each(a.begin(), a.end(), [](int i)
{
    cout << i << " ";           // -858993460 -858993460 -858993460
});
cr;

array<int, 3> b = {{ 0 }};
for_each(b.begin(), b.end(), [](int i)
{
    cout << i << " ";           // 0 0 0
});
cr;

END_TEST;




//----------------------- array as c-style array ----------------------
BEGIN_TEST(ArrayTest, CStyleArray, @);

// use array<char> as a fix sized c-string.
array<char, 100> str = {{ 0 }};

char *p = str.data();

strcpy(p, "hello world");
printf("%s\n", p);              // hello world


END_TEST;




//----------------------- normal example ----------------------
BEGIN_TEST(ArrayTest, NormalExample, @);

array<int, 5> a = {{ 1, 2, 3 }};
psln(a.size());                     // a.size() = 5;
psln(a.max_size());                 // a.max_size() = 5;
EXPECT_FALSE(a.empty());            // empty() is false.

printContainer(a, "array: ");       // array: 1 2 3 0 0

a[a.size() - 1] = 5;                // change last one
printContainer(a, "array: ");       // array: 1 2 3 0 5

a.at(a.size() - 2) = 4;
printContainer(a, "array: ");       // array: 1 2 3 4 5

int sum;
sum = accumulate(a.begin(), a.end(), 0);
psln(sum);                          // sum = 15

try
{
    int i = a.at(5);                // throw.
}
catch ( ... )
{
    pln("exception catched");
}

try
{
    //int i = a[5];                   // won't throw exception.
}
catch ( ... )
{
    pln("exception catched");       
}

// ------------------ copy ------------------
array<int, 5> a2 = a;                   // copy constructor.
printContainer(a2, "a2: ");             // a2: 1 2 3 4 5

array<int, 5> a3(a2);                   //copy ctor.
printContainer(a3, "a3: ");             // a3: 1 2 3 4 5


// ------------------ assign ------------------
array<int, 5> a4;
a4 = a3;                                // assignment operator.
printContainer(a4, "a4: ");             // a4: 1 2 3 4 5


array<int, 4> b = {};
//b = a;                                // error, b is not array<int, 5>!!


// ------------------ fill ------------------
array<int, 5> a5;
a5.fill(5);
printContainer(a5, "a5: ");             // a5: 5 5 5 5 5

// ------------------ move ------------------

// ------------------ array with class objects. ------------------




array<int, 5> a6 = {};
printContainer(a6, "a6: ");
END_TEST;


//----------------------- multiple div array example ----------------------
BEGIN_TEST(ArrayTest, MatrixOrMultipleDiv, @);

// like plain 2D array
array<array<int, 5>, 5> mat1 = {
    1,2,3,4,5,
    1,2,3,4,5,
    1,2,3,4,5,
    1,2,3,4,5,
    1,2,3,4,5,
};

// construct with 1D arys.
array<int, 5> ary = {1};
array<array<int, 5>, 5> mat2 = { ary, ary, ary, ary, ary};

// just like plain 2D array, but can ommit some value some each div.
array<array<int, 5>, 5> mat3 = {
    array<int, 5>{ 1, 2, 3, 4, 5},
    array<int, 5>{ 1, 2, 3, 4},
    array<int, 5>{ 1, 2, 3},
    array<int, 5>{ 1, 2,},
    array<int, 5>{ 1, }
};

// util function to print matrix.
auto printMatrix = [] (const array<array<int, 5>, 5>& mat) {
    for (const auto& ary : mat) {
        for (const auto& item : ary) {
            cout << item << " ";
        }
        cout << endl;
    }
};

pcln("ma1");
printMatrix(mat1);

pcln("mat2");
printMatrix(mat2);

pcln("mat3");
printMatrix(mat3);

END_TEST;


NS_END(elloop);
