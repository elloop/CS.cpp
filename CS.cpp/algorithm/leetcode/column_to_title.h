#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include <string>
#include "include/inc.h"

NS_BEGIN(elloop)
NS_BEGIN(column_to_title)

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
      elloop::printContainer(result);
      return result;
    }
};

NS_END(column_to_title)
NS_END(elloop)
