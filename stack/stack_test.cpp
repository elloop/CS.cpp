#include "stack/stack.h"
#include "inc.h"

USING_NS_ELLOOP;

int main() {
    stack<int> st;
    st.push(10000);
    auto top_elem = st.top();
    psln(top_elem);
    return 0;
}
