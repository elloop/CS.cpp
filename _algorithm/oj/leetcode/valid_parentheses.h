_Pragma("once")
#include <string>

namespace valid_parentheses {

class Solution {
  public:

    struct stack {
      stack(int capacity) {
        data = new char[capacity];
        top_ = 0;
      }
      char * data;
      bool pop() {
        if (top_ > 0) {
          --top_;
          return true;
        }
        return false;
      }
      void push(char c) {
        data[++top_] = c;
      }

      char top() {
        return data[top_];
      }

      int top_;
      ~stack() {
        delete [] data;
      }
    };

    bool isValid(std::string s) {
      int i = s.size();
      stack st(i);
      int j(0);
      for (j; j<i; ++j) {
        switch (s[j]) {
          case '(' :
          case '{':
          case '[':
            st.push(s[j]);
            break;
          case ')':
            if (st.top() == '(') {
              if (!st.pop()) {
                return false;
              }
            }
            else {
              return false;
            }
            break;
          case ']':
            if (st.top() == '[') {
              if (!st.pop()) {
                return false;
              }
            }
            else {
              return false;
            }
            break;
          case '}':
            if (st.top() == '{') {
              if (!st.pop()) {
                return false;
              }
            }
            else {
              return false;
            }
            break;
        }
      }
      return (0 == st.top_);
    }
};

}
