#include "gtest/gtest.h"
#include "inc.h"
#include "stl_headers.h"
#include <list>

NS_BEGIN(elloop);
using namespace std;

//********************************** new case **********************************
RUN_GTEST(ListTest, Example, @);

auto printList = [](const list<int> &l, const string &info="") {
    p(info);
    for (auto &i : l) {
        p(i); p(" ");
    }
    cr;
};

list<int> list1, list2;

for (int i=0; i<6; ++i) {
    list1.push_back(i);
    list2.push_front(i);
}

printList(list1, "after push, list1: ");             
printList(list2, "after push, list2: ");            



// 把list1全部移到list2中，位置是list2中第一个等于3的元素之前
list2.splice(find(begin(list2), end(list2), 3), list1);
printList(list1, "list1, after splice: ");                        // empty
printList(list2, "list2, after splice: ");   

// 把list2的第一个元素移到其末尾
list2.splice(end(list2), list2, begin(list2));
printList(list2, "list2, move begin to end: ");   

list2.sort();
list1 = list2;
list2.unique();

printList(list1, "list1, after assign: ");             
printList(list2, "list2, after sort & unique: ");            

list1.merge(list2);
printList(list1, "list1, after merge: ");
printList(list2, "list2, after merge: ");

END_TEST;

NS_END(elloop);
