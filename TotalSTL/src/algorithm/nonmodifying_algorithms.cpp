#include "nonmodifying_algorithms.h"
#include <cmath>
NS_BEGIN(elloop)
using std::vector;
using std::deque;
using std::list;

using std::for_each;
using std::count;
using std::min_element;
using std::max_element;
using std::copy;
using std::search_n;
using std::search;
using std::find_end;
using std::find_first_of;
using std::adjacent_find;

using std::modulus;
using std::bind2nd;
using std::greater;
using std::distance;
using std::make_pair;

template <typename T>
void printFunc(const T & val) {
  p(val);
  p(" ");
}

template <typename T>
class PrintFunctor {
public:
  void operator() (const T & val) {
    p(val);
    p(" ");
  }
};

BEGIN_TEST(NonModifyingAlgorithm, ForEach, @);
  pcln("NonModifyingAlgorithm");

  // for_each
  vector<int> con;
  insertElements(con, 1, 10);
  printContainer(con, "con: ");  // con: 1 2 3 4 5 6 7 8 9 10

  pcln("use lambda");               // 1 2 3 4 5 6 7 8 9 10
  for_each(con.begin(), con.end(), [](int i) {
    p(i);
    p(" ");
  });
  cr;

  pcln("use function");             // 1 2 3 4 5
  for_each(con.begin(), con.begin() + ( con.end() - con.begin() ) / 2,
    printFunc<int>);
  cr;

  pcln("use Functor");              // 10 9 8 7 6
  for_each(con.rbegin(), con.rbegin() + ( con.rend() - con.rbegin() ) / 2,
    PrintFunctor<int>());
  cr;
END_TEST;




BEGIN_TEST(NonModifyingAlgorithm, Count, @);

  vector<int> con;
  insertElements(con, 1, 10);
  printContainer(con, "con: ");  // con: 1 2 3 4 5 6 7 8 9 10

  int numOf1 = count(con.begin(), con.end(), 1);
  psln(numOf1);
  EXPECT_EQ(1, numOf1);      // one 1.
  con.push_back(1);
  con.push_back(1);
  printContainer(con, "con: ");  // con: 1 2 3 4 5 6 7 8 9 10 1 1
  numOf1 = count(con.begin(), con.end(), 1);
  psln(numOf1);
  EXPECT_EQ(3, numOf1);      // three 1.

  using std::count_if;
  int numOfEven = count_if(con.begin(), con.end(),
    [](int elem) -> bool {
    return ( elem % 2 == 0 );     // 2 4 6 8 10 -> five even.
  });
  psln(numOfEven);
  EXPECT_EQ(5, numOfEven);

END_TEST;




bool absLess(int a, int b) {
  return abs(a) < abs(b);
}



BEGIN_TEST(NonModifyingAlgorithm, MinMaxElem, @);
  deque<int> con;
  insertElements(con, 1, 10);
  insertElements(con, -5, 5);
  printContainer(con);	// con: 1 2 3 4 5 6 7 8 9 10 -5 -4 -3 -2 -1 0 1 2 3 4 5

  auto minPos = min_element(con.begin(), con.end());
  EXPECT_EQ(-5, *minPos);
  auto maxPos = max_element(con.begin(), con.end());
  EXPECT_EQ(10, *maxPos);

  auto absMinPos = min_element(con.begin(), con.end(), absLess);
  EXPECT_EQ(0, *absMinPos);
  auto absMaxPos = max_element(con.begin(), con.end(), absLess);
  EXPECT_EQ(10, *absMaxPos);
END_TEST;




BEGIN_TEST(NonModifyingAlgorithm, Find, @);
  list<int> con;
  insertElements(con, 0, 10);
  insertElements(con, 0, 5);
  printContainer(con, "con: ");	// con: 1 2 3 4 5 6 7 8 9 10 

  // copy elems between two 0 into vector.
  vector<int> between0;
  auto first0Pos = find(con.begin(), con.end(), 0);
  auto second0Pos = con.end();
  if ( first0Pos != con.end() ) {
    second0Pos = find(++first0Pos, con.end(), 0);
  }
  auto dis = distance(first0Pos, second0Pos);
  psln(dis);
  between0.resize(dis + 2);
  if ( first0Pos != con.end() && second0Pos != con.end() ) {
    copy(--first0Pos, ++second0Pos, between0.begin());
  }
  printContainer(between0, "elems between 0: ");

END_TEST;





BEGIN_TEST(NonModifyingAlgorithm, FindIf, @);
  list<int> con;
  insertElements(con, 0, 10);
  printContainer(con, "con: ");

  auto greater1Pos = find_if(con.begin(), con.end(),
    bind2nd(greater<int>(), 1));
  LOGD("first element greater than 1 is in location: %ld\n",
    distance(con.begin(), greater1Pos) + 1);
END_TEST;





BEGIN_TEST(NonModifyingAlgorithm, SearchN, @);
  deque<int> con;
  insertElements(con, 1, 10);
  printContainer(con);

  // search two consecutive 3 position.
  auto consecutive3Pos = search_n(con.begin(), con.end(), 2, 3);
  if ( consecutive3Pos != con.end() ) {
    LOGD("2 consecutive 3 found at positon: %ld\n",
      distance(con.begin(), consecutive3Pos) + 1);
  }
  else {
    pln("no 2 consecutive 3");
  }

  // search two consecutive num greater than 3.
  auto greater3 = search_n(con.begin(), con.end(), 2, 3, greater<int>());
  if ( greater3 != con.end() ) {
    LOGD("2 consecutive >3 found at positon: %ld\n",
      distance(con.begin(), greater3) + 1);
  }
  else {
    pln("no 2 consecutive >3");
  }
END_TEST;





bool checkEven(int elem, bool even) {
  if ( even ) {
    return ( elem % 2 == 0 );
  }
  else {
    return ( elem % 2 == 1 );
  }
}

BEGIN_TEST(NonModifyingAlgorithm, Search, @);
  deque<int> con;
  insertElements(con, 1, 10);
  insertElements(con, 1, 10);
  printContainer(con, "con: ");

  list<int> subCon;
  insertElements(subCon, 5, 9);
  printContainer(subCon, "subCon: ");

  // matching subCon from begin of con, return first matching start point or con.end().
  auto pos = search(con.begin(), con.end(), subCon.begin(), subCon.end());
  while ( pos != con.end() ) {
    LOGD("found match point at pos: %ld\n", distance(con.begin(), pos) + 1);
    pos = search(++pos, con.end(), subCon.begin(), subCon.end());
  }

  // matching sequence of "even odd even"
  pcln("find even odd even");
  vector<int> con2;
  insertElements(con2, 1, 7);
  printContainer(con2, "con2: ");
  bool checkArgs[] = { true, false, true };
  auto evenPos = search(con2.begin(), con2.end(), checkArgs, checkArgs + 3, checkEven);
  while ( evenPos != con2.end() ) {
    LOGD("found match point at pos: %ld\n", distance(con2.begin(), evenPos) + 1);
    evenPos = search(++evenPos, con2.end(), checkArgs, checkArgs + 3, checkEven);
  }
END_TEST;





BEGIN_TEST(NonModifyingAlgorithm, Find_End, @);
  // find_end is correspond to search, it return last occurrence of matching range.
  deque<int> con;
  insertElements(con, 1, 10);
  insertElements(con, 1, 10);
  printContainer(con, "con: ");

  list<int> subCon;
  insertElements(subCon, 5, 9);
  printContainer(subCon, "subCon: ");

  // reverse finding. Compare this with Test: Search
  auto pos = find_end(con.begin(), con.end(), subCon.begin(), subCon.end());
  while ( pos != con.end() ) {
    LOGD("found match point at pos: %ld\n", distance(con.begin(), pos) + 1);
    ++pos;
    auto newPos = find_end(con.begin(), pos, subCon.begin(), subCon.end());
    if (newPos == pos) {
      break;
    }
    pos = newPos;
  }

  // reverse finding. Compare this with Test: Search
  // matching sequence of "even odd even"
  pcln("find even odd even");
  vector<int> con2;
  insertElements(con2, 1, 7);
  printContainer(con2, "con2: ");
  bool checkArgs[] = { true, false, true };
  const int subLen = sizeof checkArgs / sizeof checkArgs[0];
  auto evenPos = find_end(con2.begin(), con2.end(), checkArgs, checkArgs + 3, checkEven);
  while ( evenPos != con2.end() ) {
    LOGD("found match point at pos: %ld\n", distance(con2.begin(), evenPos) + 1);
    ++evenPos;
    // notice: when find failed, return evenPos, because it's the end() now. Not the con2.end().
    auto newPos = find_end(con2.begin(), evenPos, checkArgs, checkArgs + 3, checkEven);
    if ( newPos == evenPos ) {
      break;
    }
    evenPos = newPos;
  }

END_TEST;





BEGIN_TEST(NonModifyingAlgorithm, Find_First_Of, @);
  vector<int> con;
  list<int> searchCon;
  insertRepeat(con, Repeat(make_pair(3, 1)));
  con.push_back(2);
  insertRepeat(con, Repeat(make_pair(3, 1)));
  con.push_back(3);
  printContainer(con, "con: ");

  searchCon.push_back(2);
  searchCon.push_back(3);
  printContainer(searchCon, "searchCon: ");

  auto firstOfElem = find_first_of(con.begin(), con.end(), searchCon.begin(), searchCon.end());
  if ( firstOfElem != con.end() ) {
    LOGD("first elem of searchCon found at location: %ld\n", distance(con.begin(), firstOfElem) + 1);
  }

  auto fromLast = find_first_of(con.rbegin(), con.rend(), searchCon.begin(), searchCon.end());
  if ( fromLast != con.rend() ) {
    LOGD("elem of searchCon (search from end of con), found at location: %ld\n", distance(con.rbegin(), fromLast) + 1);
  }

  // TODO: add examples of first_find_of using BinaryPredicate op.
  // bool op(elem, searchElem) { //...}
END_TEST;





BEGIN_TEST(NonModifyingAlgorithm, Adjacent_Find, @);
  vector<int> con;
  insertElements(con, 1, 3);
  insertRepeat(con, Repeat(make_pair(2, 5)));
  con.push_back(25);
  printContainer( con, "con: " ); // con: 1 2 3 5 5 25

  auto adjacentSamePos = adjacent_find(con.begin(), con.end());
  if ( adjacentSamePos != con.end()) {
    LOGD("first adjacent elem found at location: %ld\n", distance(con.begin(), adjacentSamePos) + 1);
  }
  else {
    pln("no adjacent");
  }

  auto condition = [](int a, int b) -> bool {
    return ( b == a*a );
  };
  auto adjacentSameWithCondition = adjacent_find(con.begin(), con.end(), condition);
  if ( adjacentSameWithCondition != con.end() ) {
    LOGD("first adjacent elem WithCondition(square) found at location: %ld\n", distance(con.begin(), adjacentSameWithCondition) + 1);
  }
  else {
    pln("no adjacent");
  }
END_TEST;




NS_END(elloop)
