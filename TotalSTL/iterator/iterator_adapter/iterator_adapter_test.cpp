#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <functional>
#include <algorithm>
#include <array>
#include <iterator>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;
using std::for_each;



//----------------------- reverse iterator  ----------------------
RUN_GTEST(IteratorAdapter, ReverseIterator, @);

vector<int> v = { 1, 2, 3 };
auto rbeg = v.rbegin();
while ( rbeg != v.rend() )
{
    cout << *rbeg << endl;
    ++rbeg;
}

array<int, 5> a = {1, 2, 3, 4, 5};
printContainer(a, "a: ");

auto pos1 = find(a.begin(), a.end(), 5);
array<int, 5>::reverse_iterator rpos1(pos1);

// rpos1 and pos1 have the same physical location.
// however, for reverse iterator, physical location is different from logical 
// location, 
// the value is stored in logical location which is before the physical location.
EXPECT_EQ(4, *rpos1);

array<int, 5>::reverse_iterator rEnd(a.end());
// rEnd also point to physical location: a.end(), 
// but its logical location is a.end() - 1, so equal to 5.
EXPECT_EQ(5, *rEnd);                    

// use base() to convert back to normal iterator.
auto recoverPos = rpos1.base();

// reverse range.
auto posA = find(a.begin(), a.end(), 2);
auto posB = find(a.begin(), a.end(), 5);
pln("in normal order: ");
copy(posA, posB, ostream_iterator<int>(cout, " "));
cr;

array<int, 5>::reverse_iterator rPosA(posA);
array<int, 5>::reverse_iterator rPosB(posB);
pln("in reverse order: ");
copy(rPosB, rPosA, ostream_iterator<int>(cout, " "));
cr;

EXPECT_EQ(5, *recoverPos);

END_TEST;




//----------------------- inserter ----------------------
RUN_GTEST(IteratorAdapter, InserterTest, @);

array<int, 5> a = { 1, 2, 3, 4, 5 };
vector<int> v = {};

//------------- 1. back inserter ----------------
// 1. back_inserter(con) : call con.push_back().
back_insert_iterator<vector<int>>  backInserter(v);
*backInserter = 1;
++backInserter;                 // do nothing, can skip this
*backInserter = 2;
++backInserter;                 // do nothing, can skip this

printContainer(v, "v: ");       // 1 2

back_inserter(v) = 3;
back_inserter(v) = 4;
printContainer(v, "v: ");       // 1 2 3 4


copy(a.begin(), a.end(), back_inserter(v));
printContainer(v, "v: ");       // 1 2 3 4 1 2 3 4 5


//------------- 2. front inserter ----------------
// front_inserter(con): call con.push_front().
list<int> l = {};

front_insert_iterator<list<int>> frontInserter(l);

*frontInserter = 1;
++frontInserter;
*frontInserter = 2;
++frontInserter;
printContainer(l, "l: ");       // 2 1

front_inserter(l) = 3;
front_inserter(l) = 4;
printContainer(l, "l: ");       // 4 3 2 1 


copy(a.begin(), a.end(), front_inserter(l));
printContainer(l, "l: ");       // 5 4 3 2 1 4 3 2 1

//------------- 3. general inserter ----------------
// inserter(con, pos) : call con.insert(), and return new valid pos.
set<int> s = {};
insert_iterator<set<int>> generalInserter(s, s.begin());
*generalInserter = 5;
++generalInserter;
*generalInserter = 1;
++generalInserter;
*generalInserter = 4;
printContainer(s, "s: ");       // 1 4 5

inserter(s, s.end()) = 3;
inserter(s, s.end()) = 2;
printContainer(s, "s: ");       // 1 2 3 4 5

list<int> copyS;
copy(s.begin(), s.end(), inserter(copyS, copyS.begin()));
printContainer(copyS, "copyS: ");       // 1 2 3 4 5

END_TEST;




//----------------------- stream iterator  ----------------------
RUN_GTEST(IteratorAdapter, StreamIterator, @);

//------------- 1. ostream iterator ----------------
// ostream_iterator(stream, delim)
ostream_iterator<int> outputInt(cout, "\n");

*outputInt = 1;             // output 1 \n
++outputInt;
*outputInt = 2;             // output 2 \n
++outputInt;
cr;

array<int, 5> a = {1, 2, 3, 4, 5};
copy(a.begin(), a.end(), ostream_iterator<int>(cout));  // no delim, 12345
cr;

string delim("-->");
copy(a.begin(), a.end(), ostream_iterator<int>(cout, delim.c_str())); 
cr;                                             // 1-->2-->3-->4-->5-->


return;                     // skip istream iterator test.

//------------- 2. istream iterator ----------------
// istream_iterator(stream)
pln("input some char, end with EOF");
istream_iterator<char> charReader(cin);

istream_iterator<char> charEof;

while (charReader != charEof)
{
    pln(*charReader);
    ++charReader;
}
cin.clear();

//------------- 3. istream & ostream & advance ----------------
pln("input some string, end with EOF");
istream_iterator<string> strReader(cin);
ostream_iterator<string> strWriter(cout);

while (strReader != istream_iterator<string>())
{
    advance(strReader, 1);
    if (strReader != istream_iterator<string>()) 
    {
        *strWriter++ = *strReader++;
    }
}
cr;

END_TEST;




    //----------------------- move iterator  ----------------------
    RUN_GTEST(IteratorAdapter, MoveIterator, @);

    list<string> l = {"hello", "tom", "jerry"};
    printContainer(l, "l: ");

    vector<string> v(l.begin(), l.end());              // copy l.
    printContainer(v, "copy of l: ");

    vector<string> v2(make_move_iterator(l.begin()), 
                   make_move_iterator(l.end()));    // move l.

    printContainer(v2, "move l to v2: ");

    // todo: l is moved, but i can still visit its elem. why?
    printContainer(l, "after moved l: ");           // still valid , why??

    END_TEST;




NS_END(elloop);
