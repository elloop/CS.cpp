#include "stack/stack.h"
#include "inc.h"

USING_NS_STD;
USING_NS_ELLOOP;

class Test {
  Test() {
    pcln("deleting test!");
  }
  ~Test() {
    pcln("deleting test!");
  }
};

int main() {
  stack<int> st;
  st.push(10000);
  auto top_elem = st.top();
  psln(top_elem);

  // stack<int> st2(st); // error: use of deleted function.
  // stack<int> st3 = move(st); // error: use of deleted function.

  // operator = is implicitly declared as deleted because stack<int> declares a move constructor or move assignment operator.

  // stack<int> st4;
  // st4 = st;
  // auto st4_top = st4.top();
  // psln(st4_top);


  shared_ptr<Test> x = new Test();


  return 0;
}
