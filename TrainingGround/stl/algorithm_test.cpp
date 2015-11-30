#include "algorithm_test.h"
#include "gtest/gtest.h"
#include "inc.h"
#include <functional>
#include <type_traits>
#include <memory>
#include <algorithm>


NS_BEGIN(elloop);


using namespace std;
using namespace std::placeholders;

<<<<<<< HEAD
BEGIN_TEST(AlgorithmTest, Basic, @)
=======
BEGIN_TEST(AlgorithmTest, Basic, @);
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340
  pcln("AlgorithmTest --> Basic");
  vector<int> vi{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
  printContainer(vi, "vi: ");

  vi.erase(vi.begin() + 2, vi.begin() + 5);

  printContainer(vi, "vi: ");

  auto pos = swap_ranges(vi.begin() + 1, vi.begin() + 3, vi.rbegin());

  if (pos.base() != vi.end()) {
    psln(*pos);

    psln(*(pos.base()));
  }

  printContainer(vi, "vi: ");
<<<<<<< HEAD
END_TEST
=======

END_TEST;
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340

std::ostream& operator<<(std::ostream& os, const PeoplePutInConainter& people) {
  people.acceptVisitor(os);
  return os;
}



<<<<<<< HEAD
BEGIN_TEST(AlgorithmTest, SortCustomClass, @)
=======
BEGIN_TEST(AlgorithmTest, SortCustomClass, @);
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340
  pcln("AlgorithmTest --> SortCustomClass");

  typedef shared_ptr<PeoplePutInConainter> Item;
  vector<Item> vp;
  vp.push_back(Item(new PeoplePutInConainter("a", 10)));
  vp.push_back(Item(new PeoplePutInConainter("c", 10)));
  vp.push_back(Item(new PeoplePutInConainter("d", 10)));
  vp.push_back(Item(new PeoplePutInConainter("b", 10)));
  vp.push_back(Item(new PeoplePutInConainter("c", 18)));
  vp.push_back(Item(new PeoplePutInConainter("a", 9)));

  // copy of vp, used for sorting greater.
  auto vpCopy = vp;

  // can not use opt="" parameter, because lambda can't use default parameter.
  auto printFunc = [](const decltype(vp)& con) {
    for (auto item : con) {
      pln(*item);   // item is PeoplePutInConainter*, it's after dereference.
    }
  };

  printFunc(vp);

  auto comparePeoplePtrLess = [](const Item& p1, const Item& p2) -> bool {
    return (*p1 < *p2);
  };

  sort(vp.begin(), vp.end(), comparePeoplePtrLess);

  pln("after sorting...");
  printFunc(vp);

  pcln("use vpCopy for greater sort");
  printFunc(vpCopy);
  auto comparePeoplePtrGreater = [](const Item& p1, const Item& p2) -> bool {
    return (*p1 > *p2);
  };
  sort(vpCopy.begin(), vpCopy.end(), comparePeoplePtrGreater);
  pln("after sorting");
  printFunc(vpCopy);

  decltype(vp)().swap(vp);
<<<<<<< HEAD

END_TEST

BEGIN_TEST(AlgorithmTest, PutObjectInSet, @)
=======
END_TEST;

BEGIN_TEST(AlgorithmTest, PutObjectInSet, @);
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340
  pcln("AlgorithmTest --> PutObjectInSet");
  set<PeoplePutInConainter> sp;
  sp.insert(PeoplePutInConainter("aa", 100));
  sp.insert(PeoplePutInConainter("aa", 100));
  sp.insert(PeoplePutInConainter("ab", 100));
  sp.insert(PeoplePutInConainter("aa", 90));

  auto print = [](decltype(sp) & con) {
    for (auto item : con) {
      pln(item);
    }
  };

  print(sp);

  sp.clear();
<<<<<<< HEAD

END_TEST
=======
END_TEST;
>>>>>>> 1e82cf24461c09c7effbaf80bd1821a35acce340


NS_END(elloop);