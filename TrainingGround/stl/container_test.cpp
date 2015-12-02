#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <type_traits>
#include <vector>
#include <list>
#include <algorithm>
#include <map>

NS_BEGIN(elloop);

using namespace std;
using namespace std::placeholders;


BEGIN_TEST(ContainerTest, DeleteFromVector, @);
  pcln("ContainerTest --> DeleteFromVector");
  vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
  printContainer(vi, "vi: ");

  auto b2(vi.begin());
  auto b4(vi.begin());
  advance(b2, 2);
  advance(b4, 4);
  vi.erase(b2, b4);
  printContainer(vi, "vi: ");

  // or simply use iter arithmetic.
  //vi.erase(vi.begin() + 2, vi.begin() + 5); 

  vector<int> vi2{ 1, 2, 3, 4, 3, 3, 5 };
  printContainer(vi2, "vi2: ");
  pln("remove all values equal to 3");
  // notice: 出于灵活性考虑，stl中remove算法只是把容器抹掉（覆盖），不会改变容器的大小等状态。
  // 还需调用成员函数erase进行删除。
  vi2.erase(remove(vi2.begin(), vi2.end(), 3), vi2.end());
  printContainer(vi2, "vi2: ");

  pcln("clear vector");
  printContainer(vi, "vi: ");
  vector<int>().swap(vi);
  printContainer(vi, "vi: ");
  printConainterInfo(vi, "vi: ");

  printContainer(vi2, "vi2: ");
  vector<int>().swap(vi2);
  printContainer(vi2, "vi2: ");

  printConainterInfo(vi2, "vi2: ");

END_TEST;

BEGIN_TEST(ContainerTest, DeleteFromList, @);
  pcln("ContainerTest --> DeleteFromList");

  list<int> li{ 1, 2, 3, 4, 5 };
  printContainer(li, "list: ");
  pln("deleting from begin + 2 to begin + 4");

  //li.remove(li.begin() + 2, li.begin() + 4); // error: list::iter is not random.
  // normal bidirectional iter use advance to move.
  auto afterBegin2(li.begin());
  auto afterBegin4(li.begin());
  advance(afterBegin2, 2);
  advance(afterBegin4, 4);
  li.erase(afterBegin2, afterBegin4);
  printContainer(li, "list: ");

  pln("deleting all value equal to 3");
  list<int> li2{ 1, 2, 3, 4, 5, 3, 3, 6 };
  printContainer(li2, "list2: ");
  // list 的 remove直接干掉元素。
  li2.remove(3);
  printContainer(li2, "list2: ");

  pcln("clear list");
  printContainer(li, "list: ");
  li.clear();
  printContainer(li, "list: ");
  printConainterInfo(li, "li: ");
  psln(li.max_size());

  printContainer(li2, "list2: ");
  li2.clear();
  printContainer(li2, "list2: ");
  printConainterInfo(li2, "list2: ");
  psln(li2.max_size());

END_TEST;

BEGIN_TEST(ContainerTest, DeleteFromSet, @);
  pcln("ContainerTest --> DeleteFromSet");

  set<int> si{ 1, 2, 3, 4, 5 };
  printContainer(si, "set1: ");
  pln("delete from begin+2 to begin+4");
  auto b2(si.begin());
  auto b4(si.begin());
  advance(b2, 2);
  advance(b4, 4);
  si.erase(b2, b4);
  printContainer(si, "set1: ");

  pcln("clear set");
  si.clear();
  printConainterInfo(si, "set: ");
  psln(si.max_size());

  set<int> si2{ 1, 2, 3, 4, 5, 6 };
  printContainer(si2, "set2: ");
  auto iter = si2.begin();
  while (iter != si2.end()) {
    si2.erase(iter++);
    // or
    //iter = si2.erase(iter);

    // don't do this
    // si2.erase(iter); ++iter; // iter is invalid after erase()
    // or 
    // iter= si2.erase(iter); ++iter; // will skip items.
  }
  printContainer(si2, "set2: ");

END_TEST;

BEGIN_TEST(ContainerTest, DeleteFromMap, @);
  pcln("ContainerTest --> DeleteFromMap");

  map<int, int> mi{ { 1, 2 }, { 4, 8 }, { 5, 10 }, { 2, 4 }, { 3, 6 } };
  printMap(mi, "map: ");
  pln("delete from begin+2 to begin+4");
  auto b2(mi.begin());
  auto b4(mi.begin());
  advance(b2, 2);
  advance(b4, 4);
  mi.erase(b2, b4);
  printMap(mi, "map: ");

  pcln("clear map");
  mi.clear();
  printMap(mi, "map: ");
  printConainterInfo(mi, "map: ");
  psln(mi.max_size());

  map<int, int> mi2{ { 1, 2 }, { 2, 4 }, { 5, 10 }, { 3, 6 }, { 4, 8 } };
  printMap(mi2, "map2: ");
  auto iter = mi2.begin();
  while (iter != mi2.end()) {
    mi2.erase(iter++);
  }
  printMap(mi2, "map2: ");
  printConainterInfo(mi2, "map: ");
  psln(mi2.max_size());
END_TEST;

BEGIN_TEST(ContainerTest, SwapSkills, @);
  pcln("ContainerTest --> SwapSkills");

  pln("delete redundant capacity");
  vector<int> vi;
  vi.reserve(100);
  vi.push_back(1);
  printContainer(vi, "vector: ");
  psln(vi.capacity());        // 100
  vector<int>(vi).swap(vi);
  psln(vi.capacity());        // 1

  pln("release vector");
  vector<int>().swap(vi);
  printContainer(vi, "vector: ");
  psln(vi.size());            // 0
  psln(vi.capacity());        // 0

END_TEST;

NS_END(elloop);
