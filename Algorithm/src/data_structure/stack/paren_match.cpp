#include "stack.h"
#include <string>
#include <iostream>

NS_BEGIN(elloop);

bool isParenMatch(const std::string &s) {
    Stack<char> st;
    for (size_t i=0; i<s.length(); ++i) {
        if (s[i] == '(') {
            st.push(s[i]);
        }
        else {
            if (st.empty()) {
                return false;
            }
            else {
                st.pop();
            }
        }
    }
    return st.empty();
}

RUN_GTEST(StackTest, ParenMatch, @@);

std::string s;

while (std::cin >> s) {
    if (isParenMatch(s)) {
        pln("match ok");
    }
    else {
        pln("match fail");
    }
}

END_TEST;

NS_END(elloop);
