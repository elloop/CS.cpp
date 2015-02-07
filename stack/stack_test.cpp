#include "stack/stack.h"
#include "stack/stack_test.h"
#include "inc.h"

USING_NS_TEST;

void StackTest::test() {
    stack<int> st;
    st.push(new int(1000));
    int* at_top = st.peek();
    if (at_top == nullptr) {
        pcln("nullptr");
    }
    else {
        psln(*at_top);
    }
}
