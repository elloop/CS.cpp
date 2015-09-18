#ifdef _MSC_VER
#pragma once
#else
_Pragma("once")
#endif

#include <string>
#include <cmath>

NS_BEGIN(elloop)
NS_BEGIN(title_to_number)

class Solution {
public:
    int titleToNumber(std::string s) {
      int result(0);
      std::string::size_type bit(0);
      auto len = s.size();
      while (bit < len) {
		  result += (s[bit] - 'A' + 1) * static_cast<int>(pow(26, len - bit - 1));
        ++bit;
      }
      return result;
    }
};

NS_END(title_to_number)
NS_END(elloop)