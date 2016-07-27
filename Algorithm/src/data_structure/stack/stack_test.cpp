#include "stack.h"
#include "inc.h"

NS_BEGIN(elloop);

RUN_GTEST(StackTest, Basic, @@);

Stack<int> st;
st.push(10);
st.push(20);
st.push(30);

psln(st.top());

st.pop();
psln(st.top());

END_TEST;


NS_END(elloop);

