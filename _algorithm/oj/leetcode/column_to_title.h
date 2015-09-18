_Pragma("once")

#include <string>
#include "inc.h"

namespace column_to_title {

class Solution {
  public:
    std::string convertToTitle(int n) {
      std::string result;
      int temp(0);
      while (n > 26) {
        temp = n - n/26 * 26;
        if (0 == temp) {
          result.insert(0, 1, 'Z');
          // remove last bit. == shift  right.
          n /= 26;
          // 'Z' will be included in next loop, substract it.
          n -= 1;
        }
        else {
          result.insert(0, 1, (n - n / 26 * 26 - 1 + 'A'));
          // remove last bit. == shift  right.
          n /= 26;
        }
      }
      result.insert(0, 1, n - 1 + 'A');
      elloop::print_container(result);
      return result;
    }
};

}
