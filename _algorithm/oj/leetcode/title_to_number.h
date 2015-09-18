_Pragma("once")
#include <string>
#include <cmath>

namespace title_to_number {

class Solution {
public:
    int titleToNumber(std::string s) {
      int result(0);
      std::string::size_type bit(0);
      std::string::size_type len = s.size();
      while (bit < len) {
        result += (s[bit] - 'A' + 1) * pow(26, len - bit - 1);
        ++bit;
      }
      return result;
    }
};

}
