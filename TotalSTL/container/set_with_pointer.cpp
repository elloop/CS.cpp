#include "container/set_with_pointer.h"
#include <set>
#include <memory>
#include <vector>
NS_BEGIN(elloop);
NS_BEGIN(set_test);

using std::set;
using std::vector;
using std::shared_ptr;

//----------------------------------- begin of new test-----------------------
BEGIN_TEST(Container, NoCustomOrder, @@);

Elem a(1),b(2),c(3),d(4);
ps(&a); p(" "); psln(a.weight_);
ps(&b); p(" "); psln(b.weight_);
ps(&c); p(" "); psln(c.weight_);
ps(&d); p(" "); psln(d.weight_);

// default sort method is less<Elem*>, which behaves like less<int>
// so the elems will be in ascending order of pointer address. 
set<Elem*>  elems;
elems.insert(&a);
elems.insert(&b);
elems.insert(&c);
elems.insert(&d);
printContainer(elems, "elems: ");

END_TEST;

//----------------------------------- begin of new test-----------------------
BEGIN_TEST(Container, WithCustomOrder, @@);

ElemWithLess a(1), b(2), c(3), d(4);
ps(&a); p(" "); psln(a.weight_);
ps(&b); p(" "); psln(b.weight_);
ps(&c); p(" "); psln(c.weight_);
ps(&d); p(" "); psln(d.weight_);

// elems will use less<ElemWithLess*> as sort criterion.
// less<ElemWithLess*> is defined in `set_with_pointer.h`
// elems will be in ascending order of weight.
set<ElemWithLess*>  elems;
elems.insert(&a);
elems.insert(&b);
elems.insert(&c);
elems.insert(&d);
printContainer(elems, "elems: ");

END_TEST;


//----------------------------------- begin of new test-----------------------
BEGIN_TEST(Container, ModifyElem, @@);

set<int> is;

is.insert(10);
auto iter = is.begin();
//*iter = 100;  // error

vector<int> iv;
iv.push_back(10);
(*(iv.begin())) = 100;  // ok.

END_TEST;
NS_END(set_test);
NS_END(elloop);